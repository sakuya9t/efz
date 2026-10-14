#!/bin/bash
# Download and lay out the toolchain efz.exe was built with:
#   msvc71/    Visual C++ Toolkit 2003 1.01 (cl/link 13.10.3077 / 7.10.3077, CRT libs),
#              plus cvtres.exe 7.10.3052 from the .NET Framework 1.1
#   psdk/      Windows Server 2003 SP1 Platform SDK headers and x86 libs
#   psdk2003/  the February 2003 Platform SDK's gdi32.lib, winmm.lib and rc.exe, which
#              efz.exe was linked with (Visual Studio .NET 2003 shipped that release)
#   vs2003/    user32.lib as Visual Studio .NET 2003 had it, derived from the February
#              2003 one by user32lib.py (its own copy isn't freely available)
#   dxsdk/     DirectX 9.0c SDK (August 2005) headers and x86 libs
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
# pin the archive.org copies that were checked against those signatures. (Of the
# February 2003 Platform SDK's 13 volumes only the first is signed, but the setup
# cabinets taken from them are signed too.)
psdk2003=https://archive.org/download/psdk-full.-1/Feb%202003
downloads=(
    "VCToolkitSetup-1.01.exe 50dc6cca1503f08a41d56816f3f1abcaf347b0bd https://archive.org/download/20260623_202606/VCToolkitSetup.exe"
    "en_ws_2003_sp1_sdk_april_2005.iso ee43b337d9739a4da3417b8eaca36cfafaa41de7 https://archive.org/download/platform-sdk-from-microsoft-windows-server-2003-with-service-pack-1-april-2005-edition-english/en_ws_2003_sp1_sdk_april_2005.iso"
    "dxsdk_aug2005.exe 67b14c622f80481c433414837d43b6ed5b97f4d8 https://archive.org/download/dxsdk_aug2005/dxsdk_aug2005.exe"
    "dotnetfx11.exe 16a354a2207c4c8846b617cbc78f7b7c1856340e https://archive.org/download/dotnetfx_202102/dotnetfx.exe"
    "psdk-feb2003/PSDK-FULL.1.cab 698345bf8ca8afd6f7e23fb0f9bf65b69d9f9576 $psdk2003/PSDK-FULL.1.cab"
    "psdk-feb2003/PSDK-FULL.2.cab 1889b49d9deb58800d0209d2647d7c2620ee8fb5 $psdk2003/PSDK-FULL.2.cab"
    "psdk-feb2003/PSDK-FULL.3.cab 655c9b9cd381fe15afc4964f543d756e13ec245e $psdk2003/PSDK-FULL.3.cab"
    "psdk-feb2003/PSDK-FULL.4.cab 798a516764061a9c14dcee38db1fda967412345f $psdk2003/PSDK-FULL.4.cab"
    "psdk-feb2003/PSDK-FULL.5.cab 4eab29210cbe9be846b245b2264ea0bc4b6dea9e $psdk2003/PSDK-FULL.5.cab"
    "psdk-feb2003/PSDK-FULL.6.cab 19c9ff0e237d579559c8c10eb9bae8db3b753c91 $psdk2003/PSDK-FULL.6.cab"
    "psdk-feb2003/PSDK-FULL.7.cab 674c8e001e05e7c9063dfade5818af2994c11a90 $psdk2003/PSDK-FULL.7.cab"
    "psdk-feb2003/PSDK-FULL.8.cab b50a356a481ac6b9c86d34ec96973cc3e325b419 $psdk2003/PSDK-FULL.8.cab"
    "psdk-feb2003/PSDK-FULL.9.cab f18b3fc435f45e8d21cbda422b24b1b2705e5ecb $psdk2003/PSDK-FULL.9.cab"
    "psdk-feb2003/PSDK-FULL.10.cab 6dded60cc2e551ebec2693eab85f4967528f802a $psdk2003/PSDK-FULL.10.cab"
    "psdk-feb2003/PSDK-FULL.11.cab 1d8932bb16a8257aee95ab2923605ff53e0b0412 $psdk2003/PSDK-FULL.11.cab"
    "psdk-feb2003/PSDK-FULL.12.cab 94a40b3c954c08d6db624fa4db6bd2de841b34d5 $psdk2003/PSDK-FULL.12.cab"
    "psdk-feb2003/PSDK-FULL.13.cab f69a071f3d82c464dee020760acd423af539e4bf $psdk2003/PSDK-FULL.13.cab"
)
for entry in "${downloads[@]}"; do
    read -r file sha1 url <<<"$entry"
    if ! echo "$sha1  $cache/$file" | sha1sum -c --quiet 2>/dev/null; then
        echo "downloading $file"
        mkdir -p "$(dirname "$cache/$file")"
        curl -fSL -o "$cache/$file.part" "$url"
        echo "$sha1  $cache/$file.part" | sha1sum -c --quiet
        mv "$cache/$file.part" "$cache/$file"
    fi
done

docker build -q --build-arg UID="$(id -u)" --build-arg GID="$(id -g)" -t efz-msvc71 "$here" >/dev/null

docker run --rm --network none -v "$here:/toolchain:ro" -v "$cache:/cache:ro" -v "$dest:/dest" \
    efz-msvc71 bash -euo pipefail -c '
work=$(mktemp -d)
rm -rf /dest/msvc71 /dest/psdk /dest/psdk2003 /dest/vs2003 /dest/dxsdk

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

echo "extracting the February 2003 Platform SDK libraries and rc.exe"
7z x -y -o"$work/p3" /cache/psdk-feb2003/PSDK-FULL.1.cab setup/CoreSDK-common.2.0.cab \
    setup/CoreSDK-common.2.1.cab setup/CoreSDK-x86.3.0.cab >/dev/null
for c in "$work"/p3/setup/*.cab; do 7z x -y -o"$work/p3/files" "$c" >/dev/null; done
# The setup cabinets name files by their MSI keys; these are the x86 ones.
f="$work/p3/files"
mkdir -p /dest/psdk2003/Lib /dest/psdk2003/Bin /dest/vs2003/Lib
cp "$f/Gdi32_Lib.EE6D822F_F27C_44A2_8A2F_707E2C2210B7" /dest/psdk2003/Lib/Gdi32.Lib
cp "$f/WinMM_Lib.95CE7E01_A68D_11D2_A852_00C04FC2A854" /dest/psdk2003/Lib/WinMM.Lib
cp "$f/RC_Exe.95CE7C1E_A68D_11D2_A852_00C04FC2A854" /dest/psdk2003/Bin/rc.exe
cp "$f/RcDll_Dll.95CE7C1F_A68D_11D2_A852_00C04FC2A854" /dest/psdk2003/Bin/rcdll.dll
python3 /toolchain/user32lib.py "$f/User32_Lib.95CE7DF8_A68D_11D2_A852_00C04FC2A854" \
    /dest/vs2003/Lib/User32.Lib

echo "extracting cvtres.exe from the .NET Framework 1.1"
7z x -y -o"$work/fx" /cache/dotnetfx11.exe netfx.msi netfx1.cab >/dev/null
(cd "$work/fx" && msiextract netfx.msi >/dev/null)
find "$work/fx" -name cvtres.exe -exec cp {} /dest/msvc71/bin/cvtres.exe \;
test -f /dest/msvc71/bin/cvtres.exe

rm -rf "$work"
cd /tmp && wine /dest/msvc71/bin/cl.exe 2>&1 | head -1
'
echo "toolchain ready in $dest"
