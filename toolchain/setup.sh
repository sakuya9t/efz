#!/bin/bash
# Download and lay out the toolchain efz.exe was built with:
#   msvc71/  Visual C++ Toolkit 2003 1.01 (cl/link 13.10.3077 / 7.10.3077, CRT libs)
#   psdk/    Windows Server 2003 SP1 Platform SDK headers and x86 libs
#   dxsdk/   DirectX 9.0c SDK (August 2005) headers and x86 libs
# into $EFZ_TOOLCHAIN (default ~/tools/efz-toolchain), and build the efz-msvc71 wine
# image.  Needs docker, curl and sha1sum on the host; extraction runs in the container.
# Downloads are cached in $EFZ_TOOLCHAIN_CACHE (default $EFZ_TOOLCHAIN/downloads).
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
dest=${EFZ_TOOLCHAIN:-$HOME/tools/efz-toolchain}
cache=${EFZ_TOOLCHAIN_CACHE:-$dest/downloads}
mkdir -p "$dest" "$cache"
dest=$(cd "$dest" && pwd)
cache=$(cd "$cache" && pwd)

# name, sha1, url.  The installers are Microsoft's, Authenticode-signed; the hashes
# pin the archive.org copies that were checked against those signatures.
downloads=(
    "VCToolkitSetup-1.01.exe 50dc6cca1503f08a41d56816f3f1abcaf347b0bd https://archive.org/download/20260623_202606/VCToolkitSetup.exe"
    "en_ws_2003_sp1_sdk_april_2005.iso ee43b337d9739a4da3417b8eaca36cfafaa41de7 https://archive.org/download/platform-sdk-from-microsoft-windows-server-2003-with-service-pack-1-april-2005-edition-english/en_ws_2003_sp1_sdk_april_2005.iso"
    "dxsdk_aug2005.exe 67b14c622f80481c433414837d43b6ed5b97f4d8 https://archive.org/download/dxsdk_aug2005/dxsdk_aug2005.exe"
)
for entry in "${downloads[@]}"; do
    read -r file sha1 url <<<"$entry"
    if ! echo "$sha1  $cache/$file" | sha1sum -c --quiet 2>/dev/null; then
        echo "downloading $file"
        curl -fSL -o "$cache/$file.part" "$url"
        echo "$sha1  $cache/$file.part" | sha1sum -c --quiet
        mv "$cache/$file.part" "$cache/$file"
    fi
done

docker build -q --build-arg UID="$(id -u)" --build-arg GID="$(id -g)" -t efz-msvc71 "$here" >/dev/null

docker run --rm --network none -v "$here:/toolchain:ro" -v "$cache:/cache:ro" -v "$dest:/dest" \
    efz-msvc71 bash -euo pipefail -c '
work=$(mktemp -d)
rm -rf /dest/msvc71 /dest/psdk /dest/dxsdk

echo "extracting Visual C++ Toolkit 2003"
7z x -y -o"$work/tk" /cache/VCToolkitSetup-1.01.exe "[0]" >/dev/null
python3 /toolchain/isunpack.py "$work/tk/[0]" "$work/tk/is" >/dev/null
(cd "$work/tk" && msiextract "is/Microsoft Visual C++ Toolkit 2003.msi" >/dev/null)
mkdir -p /dest/msvc71
cp -r "$work/tk/Program Files/Microsoft Visual C++ Toolkit 2003/"{bin,include,lib} /dest/msvc71/

echo "extracting Platform SDK"
7z x -y -o"$work/iso" /cache/en_ws_2003_sp1_sdk_april_2005.iso Setup >/dev/null
(mkdir "$work/psdk" && cd "$work/psdk" && msiextract "$work/iso/Setup/PSDK-x86.msi" >/dev/null)
sdk="$work/psdk/SOURCEDIR/Program Files/Microsoft Platform SDK:."
mkdir -p /dest/psdk/Lib
cp -r "$sdk/Include" /dest/psdk/Include
cp -rn "$sdk/include/." /dest/psdk/Include/
find "$sdk/Lib" -maxdepth 1 -type f -exec cp {} /dest/psdk/Lib/ \;

echo "extracting DirectX SDK"
7z x -y -o"$work/dx" /cache/dxsdk_aug2005.exe >/dev/null
7z x -y -o"$work/dx/sdk" "$work/dx/dxsdk.exe" "Include/*" "Lib/x86/*" >/dev/null
mkdir -p /dest/dxsdk
cp -r "$work/dx/sdk/Include" /dest/dxsdk/Include
cp -r "$work/dx/sdk/Lib/x86" /dest/dxsdk/Lib

rm -rf "$work"
cd /tmp && wine /dest/msvc71/bin/cl.exe 2>&1 | head -1
'
echo "toolchain ready in $dest"
