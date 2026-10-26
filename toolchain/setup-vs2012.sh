#!/bin/bash
# Download and lay out the toolchain EfzRevival 1.02h was built with:
#   vs2012/    Visual C++ 2012 Update 4 (cl, c1, link 17.00/11.00.61030, CRT libs 50929)
#              with Update 5's c1xx.dll and c2.dll (17.00.61219) over it, which is what
#              an Update 5 install has.  Objects get c2's build in their @comp.id, so
#              the Rich headers of all three 1.02h binaries show 61219 for the developer's
#              own objects, 50929 for the CRT and a 61030 linker; their 61030 C and C++
#              objects are prebuilt libraries (boost and its zlib).
#   sdk71a/    Windows SDK 7.1A, the v110_xp platform SDK (its import libraries are the
#              Implib900 30729 objects in the Rich headers)
#   dxsdk2010/ DirectX SDK (June 2010) headers and x86 libs, for DDRAW.dll's d3d9 and
#              d3dx9_43 imports
#   boost156/  boost 1.56.0 headers and its official msvc-11.0 static libraries
#              (-mt-s), whose code is the binaries' boost code (docs/revival.md)
#   protobuf-2.6.1/, zlib-1.2.8/
#              sources: the launcher compiles protobuf's lite runtime and gzip stream
#              (with zlib's headers) itself
# into $EFZ_TOOLCHAIN (default ~/tools/efz-toolchain), using the efz-msvc71 wine image
# that toolchain/setup.sh builds.
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
dest=${EFZ_TOOLCHAIN:-$HOME/tools/efz-toolchain}
cache=${EFZ_TOOLCHAIN_CACHE:-$dest/downloads}/vs2012
mkdir -p "$dest" "$cache"
dest=$(cd "$dest" && pwd)
cache=$(cd "$cache" && pwd)

# name, sha1, url.  The Update 5 ISO is Microsoft's (my.visualstudio.com) as archived;
# the DirectX SDK is still on download.microsoft.com.
downloads=(
    "VS2012.5.iso b28241ca909e909a9bb43fbec3358c0d1bc26b5f https://archive.org/download/vs-2012.5_202610/VS2012.5.iso"
    "DXSDK_Jun10.exe 495ad05ae5fc4ecd76b53a69a35bacb66d958608 https://download.microsoft.com/download/A/E/7/AE743F1F-632B-4809-87A9-AA1BB3458E31/DXSDK_Jun10.exe"
    "boost_1_56_0-msvc-11.0-32.exe 6ac113f753836102ca993b1d5320d44432995683 https://sourceforge.net/projects/boost/files/boost-binaries/1.56.0/boost_1_56_0-msvc-11.0-32.exe/download"
    "protobuf-2.6.1.tar.gz 375765455ad49e45e4e10364f91aaf2831d3e905 https://github.com/protocolbuffers/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz"
    "zlib-1.2.8.tar.gz a4d316c404ff54ca545ea71a27af7dbc29817088 https://zlib.net/fossils/zlib-1.2.8.tar.gz"
)
for entry in "${downloads[@]}"; do
    read -r file sha1 url <<<"$entry"
    if ! echo "$sha1  $cache/$file" | sha1sum -c --quiet 2>/dev/null; then
        echo "downloading $file"
        curl -fSL -A Wget -o "$cache/$file.part" "$url"
        echo "$sha1  $cache/$file.part" | sha1sum -c --quiet
        mv "$cache/$file.part" "$cache/$file"
    fi
done

docker build -q --build-arg UID="$(id -u)" --build-arg GID="$(id -g)" -t efz-msvc71 "$here" >/dev/null

docker run --rm --network none -v "$cache:/cache:ro" -v "$dest:/dest" \
    efz-msvc71 bash -euo pipefail -c '
work=$(mktemp -d)
rm -rf /dest/vs2012 /dest/sdk71a /dest/dxsdk2010 /dest/boost156 /dest/protobuf-2.6.1 /dest/zlib-1.2.8

echo "extracting Visual C++ 2012"
7z x -y -o"$work/iso" /cache/VS2012.5.iso packages/vc_compilercore86 \
    packages/vc_compilercore86res/enu packages/vc_librarycore86 packages/XPSupport \
    packages/KB2707250vc >/dev/null
# (msiextract exits 0 even when it cannot open the package.)
for p in vc_compilercore86/vc_compilercore86 vc_compilercore86res/enu/vc_compilercore86res \
         vc_librarycore86/vc_librarycore86 XPSupport/Win_XPSupport; do
    pkg=${p%%/*}
    mkdir -p "$work/$pkg"
    (cd "$work/iso/packages/${p%/*}" && msiextract -C "$work/$pkg" "${p##*/}.msi" >/dev/null)
done
vc="Program Files/Microsoft Visual Studio 11.0/VC"
mkdir -p /dest/vs2012
cp -r "$work/vc_compilercore86/$vc/bin" /dest/vs2012/bin
cp -r "$work/vc_compilercore86res/$vc/bin/1033" /dest/vs2012/bin/1033
rm -rf /dest/vs2012/bin/x86_amd64
cp -r "$work/vc_librarycore86/$vc/include" /dest/vs2012/include
mkdir -p /dest/vs2012/lib
find "$work/vc_librarycore86/$vc/lib" -maxdepth 1 -type f -exec cp {} /dest/vs2012/lib/ \;
# The compiler DLLs need mspdb110.dll and friends beside cl.exe, and the PDB server
# mspdbsrv.exe for /Zi and link /DEBUG.
find "$work/vc_compilercore86" -iname "mspdb*" -exec cp -n {} /dest/vs2012/bin/ \;
find "$work/vc_compilercore86" -iname "msobj110.dll" -exec cp -n {} /dest/vs2012/bin/ \;

echo "applying Update 5 (c1xx.dll, c2.dll 17.00.61219)"
7z x -y -o"$work/u5" "$work/iso/packages/KB2707250vc/VS11-KB2707250vc.msp" \
    WinC_compiler_x86_c1xx.dll_F WinC_common_x86_c2.dll_F >/dev/null
cp "$work/u5/WinC_compiler_x86_c1xx.dll_F" /dest/vs2012/bin/c1xx.dll
cp "$work/u5/WinC_common_x86_c2.dll_F" /dest/vs2012/bin/c2.dll

echo "extracting Windows SDK 7.1A"
sdk="$work/XPSupport/Program Files/Microsoft SDKs/Windows/v7.1A"
mkdir -p /dest/sdk71a/Lib
cp -r "$sdk/Include" /dest/sdk71a/Include
find "$sdk/Lib" -maxdepth 1 -type f -exec cp {} /dest/sdk71a/Lib/ \;
cp -r "$sdk/Bin" /dest/sdk71a/Bin

echo "extracting DirectX SDK (June 2010)"
7z x -y -o"$work/dx" /cache/DXSDK_Jun10.exe "DXSDK/Include/*" "DXSDK/Lib/x86/*" >/dev/null
mkdir -p /dest/dxsdk2010
cp -r "$work/dx/DXSDK/Include" /dest/dxsdk2010/Include
cp -r "$work/dx/DXSDK/Lib/x86" /dest/dxsdk2010/Lib

echo "extracting boost 1.56.0"
(mkdir "$work/boost" && cd "$work/boost" &&
    innoextract -s -q -I app/boost -I app/lib32-msvc-11.0 /cache/boost_1_56_0-msvc-11.0-32.exe)
mkdir -p /dest/boost156/lib
cp -r "$work/boost/app/boost" /dest/boost156/boost
cp "$work/boost/app/lib32-msvc-11.0/"libboost_*-vc110-mt-s-1_56.lib /dest/boost156/lib/

echo "extracting protobuf 2.6.1 and zlib 1.2.8"
tar -xzf /cache/protobuf-2.6.1.tar.gz -C /dest
tar -xzf /cache/zlib-1.2.8.tar.gz -C /dest

rm -rf "$work"
cd /tmp && wine /dest/vs2012/bin/cl.exe 2>&1 | head -1
'
echo "VS2012 toolchain ready in $dest"
