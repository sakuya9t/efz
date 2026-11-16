#!/bin/bash
# toolchain/setup-vs2012.sh's toolchain, laid out natively on Windows (Git Bash), with no
# container and no administrator rights: the same downloads and the same layout in
# $EFZ_TOOLCHAIN (default ~/tools/efz-toolchain), which tools/msvc11 then runs directly.
# The container's 7z, msiextract and innoextract are 7-Zip, lessmsi and innoextract's
# Windows builds here. It also puts in $EFZ_TOOLCHAIN/bin what the Makefile needs and
# Git Bash lacks: GNU make (MSYS2's package, which runs on Git Bash's runtime), and
# python3, a Python 3.12 environment with pefile made by uv. Use it with
#   export PATH=~/tools/efz-toolchain/bin:$PATH
set -euo pipefail

dest=${EFZ_TOOLCHAIN:-$HOME/tools/efz-toolchain}
cache=${EFZ_TOOLCHAIN_CACHE:-$dest/downloads}
bin=$dest/bin
mkdir -p "$cache/vs2012" "$cache/tools" "$bin"
dest=$(cd "$dest" && pwd)
# Windows programs get Windows paths.
w() { cygpath -w "$1"; }

# fetch DIR NAME SHA URL: download unless DIR/NAME has the digest (SHA-1 or SHA-256 by
# its length).
fetch() {
    local dir=$1 file=$2 sha=$3 url=$4 sum=sha256sum
    [ ${#sha} = 40 ] && sum=sha1sum
    if ! echo "$sha  $dir/$file" | $sum -c --quiet 2> /dev/null; then
        echo "downloading $file"
        curl -fSL -A Wget -o "$dir/$file.part" "$url"
        echo "$sha  $dir/$file.part" | $sum -c --quiet
        mv "$dir/$file.part" "$dir/$file"
    fi
}
# toolchain/setup-vs2012.sh's downloads
fetch "$cache/vs2012" VS2012.5.iso b28241ca909e909a9bb43fbec3358c0d1bc26b5f \
    https://archive.org/download/vs-2012.5_202610/VS2012.5.iso
fetch "$cache/vs2012" DXSDK_Jun10.exe 495ad05ae5fc4ecd76b53a69a35bacb66d958608 \
    https://download.microsoft.com/download/A/E/7/AE743F1F-632B-4809-87A9-AA1BB3458E31/DXSDK_Jun10.exe
fetch "$cache/vs2012" boost_1_56_0-msvc-11.0-32.exe 6ac113f753836102ca993b1d5320d44432995683 \
    https://sourceforge.net/projects/boost/files/boost-binaries/1.56.0/boost_1_56_0-msvc-11.0-32.exe/download
fetch "$cache/vs2012" protobuf-2.6.1.tar.gz 375765455ad49e45e4e10364f91aaf2831d3e905 \
    https://github.com/protocolbuffers/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
fetch "$cache/vs2012" zlib-1.2.8.tar.gz a4d316c404ff54ca545ea71a27af7dbc29817088 \
    https://zlib.net/fossils/zlib-1.2.8.tar.gz
# and the tools
t=$cache/tools
fetch "$t" 7zr.exe 256feca8e274e5da655e2a284fabafd9f554365eb164862089dacd4e8276d282 \
    https://www.7-zip.org/a/7zr.exe
fetch "$t" 7z2409-x64.exe bdd1a33de78618d16ee4ce148b849932c05d0015491c34887846d431d29f308e \
    https://www.7-zip.org/a/7z2409-x64.exe
fetch "$t" innoextract-1.9-windows.zip 6989342c9b026a00a72a38f23b62a8e6a22cc5de69805cf47d68ac2fec993065 \
    https://constexpr.org/innoextract/files/innoextract-1.9-windows.zip
fetch "$t" lessmsi-v2.12.9.zip 5b4e187e74b184ad3a63ccf06c3d17dae2b8c4b6c298a996dbd51a9f6db29d21 \
    https://github.com/activescott/lessmsi/releases/download/v2.12.9/lessmsi-v2.12.9.zip
fetch "$t" make-4.4.1-3-x86_64.pkg.tar.zst af0bdba17f06fe037f0194069adaa31a8fe45f1a11381501896aea1fae37bd5d \
    https://repo.msys2.org/msys/x86_64/make-4.4.1-3-x86_64.pkg.tar.zst
fetch "$t" uv-0.13.7.zip 0cdc5b38fe5a8168ed6a25814f5ba43c21d313dd3187314fccb37b7cec46e021 \
    https://github.com/astral-sh/uv/releases/download/0.13.7/uv-x86_64-pc-windows-msvc.zip

echo "installing the tools"
work=$(mktemp -d -p "$dest")
trap 'rm -rf "$work"' EXIT
"$t/7zr.exe" x -y "-o$(w "$work/7zip")" "$(w "$t/7z2409-x64.exe")" > /dev/null
cp "$work/7zip/7z.exe" "$work/7zip/7z.dll" "$bin/"
unzip -o -q "$t/innoextract-1.9-windows.zip" innoextract.exe -d "$bin"
rm -rf "$dest/lessmsi" && unzip -o -q "$t/lessmsi-v2.12.9.zip" -d "$dest/lessmsi"
"$bin/7z.exe" x -so "$(w "$t/make-4.4.1-3-x86_64.pkg.tar.zst")" 2> /dev/null |
    tar -xO -f - usr/bin/make.exe > "$bin/make.exe"
unzip -o -q "$t/uv-0.13.7.zip" uv.exe -d "$bin"
UV_PYTHON_INSTALL_DIR="$dest/python" UV_CACHE_DIR="$dest/uv-cache" \
    "$bin/uv.exe" venv -q --allow-existing --python 3.12 "$dest/venv"
UV_CACHE_DIR="$dest/uv-cache" "$bin/uv.exe" pip install -q --python "$dest/venv/Scripts/python.exe" pefile
printf '#!/bin/sh\nexec "%s" "$@"\n' "$dest/venv/Scripts/python.exe" > "$bin/python3"
chmod +x "$bin/python3"

# A link's PDB server outlives it and keeps its directory busy.
if [ -x "$dest/vs2012/bin/mspdbsrv.exe" ]; then
    "$dest/vs2012/bin/mspdbsrv.exe" -stop > /dev/null 2>&1 || true
    sleep 2
fi
rm -rf "$dest/vs2012" "$dest/sdk71a" "$dest/dxsdk2010" "$dest/boost156" "$dest/protobuf-2.6.1" \
    "$dest/zlib-1.2.8"
echo "extracting Visual C++ 2012"
"$bin/7z.exe" x -y "-o$(w "$work/iso")" "$(w "$cache/vs2012/VS2012.5.iso")" \
    packages/vc_compilercore86 packages/vc_compilercore86res/enu packages/vc_librarycore86 \
    packages/XPSupport packages/KB2707250vc packages/vc_libraryextended > /dev/null
# lessmsi x PACKAGE DIR\ lays the package out in DIR\SourceDir, as msiextract does in DIR.
for p in vc_compilercore86/vc_compilercore86 vc_compilercore86res/enu/vc_compilercore86res \
         vc_librarycore86/vc_librarycore86 XPSupport/Win_XPSupport \
         vc_libraryextended/vc_libraryextended; do
    (cd "$work/iso/packages/${p%/*}" &&
        "$dest/lessmsi/lessmsi.exe" x "${p##*/}.msi" "$(w "$work/${p%%/*}")\\" > /dev/null)
done
vc="SourceDir/Program Files/Microsoft Visual Studio 11.0/VC"
mkdir -p "$dest/vs2012/lib" "$dest/vs2012/atlmfc/lib"
cp -r "$work/vc_compilercore86/$vc/bin" "$dest/vs2012/bin"
cp -r "$work/vc_compilercore86res/$vc/bin/1033" "$dest/vs2012/bin/1033"
rm -rf "$dest/vs2012/bin/x86_amd64"
cp -r "$work/vc_librarycore86/$vc/include" "$dest/vs2012/include"
find "$work/vc_librarycore86/$vc/lib" -maxdepth 1 -type f -exec cp {} "$dest/vs2012/lib/" \;
cp -r "$work/vc_libraryextended/$vc/atlmfc/include" "$dest/vs2012/atlmfc/include"
find "$work/vc_libraryextended/$vc/atlmfc/lib" -maxdepth 1 -type f -name "*.lib" \
    -exec cp {} "$dest/vs2012/atlmfc/lib/" \;
find "$work/vc_compilercore86" -iname "mspdb*" -exec cp -n {} "$dest/vs2012/bin/" \;
find "$work/vc_compilercore86" -iname "msobj110.dll" -exec cp -n {} "$dest/vs2012/bin/" \;

echo "applying Update 5 (c1xx.dll, c2.dll 17.00.61219)"
"$bin/7z.exe" x -y "-o$(w "$work/u5")" "$(w "$work/iso/packages/KB2707250vc/VS11-KB2707250vc.msp")" \
    WinC_compiler_x86_c1xx.dll_F WinC_common_x86_c2.dll_F > /dev/null
cp "$work/u5/WinC_compiler_x86_c1xx.dll_F" "$dest/vs2012/bin/c1xx.dll"
cp "$work/u5/WinC_common_x86_c2.dll_F" "$dest/vs2012/bin/c2.dll"

echo "extracting Windows SDK 7.1A"
sdk="$work/XPSupport/SourceDir/Program Files/Microsoft SDKs/Windows/v7.1A"
mkdir -p "$dest/sdk71a/Lib"
cp -r "$sdk/Include" "$dest/sdk71a/Include"
find "$sdk/Lib" -maxdepth 1 -type f -exec cp {} "$dest/sdk71a/Lib/" \;
cp -r "$sdk/Bin" "$dest/sdk71a/Bin"
cp "$sdk/Bin/RC.Exe" "$dest/vs2012/bin/rc.exe"
cp "$sdk/Bin/RcDll.Dll" "$dest/vs2012/bin/rcdll.dll"

echo "extracting DirectX SDK (June 2010)"
"$bin/7z.exe" x -y "-o$(w "$work/dx")" "$(w "$cache/vs2012/DXSDK_Jun10.exe")" \
    "DXSDK/Include/*" "DXSDK/Lib/x86/*" > /dev/null
mkdir -p "$dest/dxsdk2010"
cp -r "$work/dx/DXSDK/Include" "$dest/dxsdk2010/Include"
cp -r "$work/dx/DXSDK/Lib/x86" "$dest/dxsdk2010/Lib"

echo "extracting boost 1.56.0"
# (innoextract's Windows build matches paths with backslashes)
mkdir "$work/boost"
(cd "$work/boost" && "$bin/innoextract.exe" -s -q -I 'app\boost' -I 'app\lib32-msvc-11.0' \
    "$(w "$cache/vs2012/boost_1_56_0-msvc-11.0-32.exe")")
mkdir -p "$dest/boost156/lib"
cp -r "$work/boost/app/boost" "$dest/boost156/boost"
cp "$work/boost/app/lib32-msvc-11.0/"libboost_*-vc110-mt-s-1_56.lib "$dest/boost156/lib/"

echo "extracting protobuf 2.6.1 and zlib 1.2.8"
tar -xzf "$cache/vs2012/protobuf-2.6.1.tar.gz" -C "$dest"
tar -xzf "$cache/vs2012/zlib-1.2.8.tar.gz" -C "$dest"

rm -rf "$work"
"$dest/vs2012/bin/cl.exe" 2>&1 | head -1
echo "VS2012 toolchain ready in $dest; export PATH=$bin:\$PATH"
