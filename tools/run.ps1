# Build the native game from this checkout and start it, on Windows. tools\run.cmd runs
# this, past PowerShell's policy against running scripts:
#   tools\run.cmd --data C:\path\to\EFZ   the game, built first if anything changed
#   tools\run.cmd --build-only            only build
# Every other option goes to the game (port/main.cpp): --save DIR, --fullscreen...
# --data is the folder of an EFZ 4.02 install, the one with the system folder. Without
# it the game's data is %EFZ_DATA%, %EFZ_DIR% or the current folder.
#
# The build is CMakeLists.txt's in build\run, of the build type the replay test checks
# (RelWithDebInfo); the first one downloads SDL3 and takes a few minutes. It needs CMake
# 3.16 or later and Visual Studio 2019 or later with its C++ tools (the Build Tools are
# enough, and bring a CMake), or MinGW-w64's g++ with Ninja or mingw32-make.

function Die($message) {
    [Console]::Error.WriteLine("tools\run: $message")
    exit 1
}
function Have($name) {
    return [bool](Get-Command $name -ErrorAction SilentlyContinue)
}

$repo = Split-Path -Parent $PSScriptRoot
$buildOnly = $false
$data = $false
$gameArgs = @()
foreach ($a in $args) {
    if ($a -eq '--build-only') {
        $buildOnly = $true
        continue
    }
    if ($a -eq '--data') {
        $data = $true
    }
    $gameArgs += "$a"
}
# Checked before building, which can take minutes. The game checks the folder itself.
if (-not $buildOnly -and -not $data -and -not $env:EFZ_DATA) {
    if ($env:EFZ_DIR) {
        $gameArgs += '--data', $env:EFZ_DIR
    } elseif (-not (Test-Path -PathType Container 'system')) {
        Die ("where is the game? Pass --data DIR, the folder of an EFZ 4.02 install`n" +
             "(with its system folder), or set EFZ_DIR to it")
    }
}

# Visual Studio, and the CMake it brings if there is none on the PATH.
$vs = $null
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vswhere) {
    $vs = & $vswhere -latest -products * -requiresAny -requires `
        Microsoft.VisualStudio.Component.VC.Tools.x86.x64 Microsoft.VisualStudio.Component.VC.Tools.ARM64 `
        -property installationPath | Select-Object -First 1
}
$cmake = $null
if (Have cmake) {
    $cmake = (Get-Command cmake).Path
} else {
    $places = @("$env:ProgramFiles\CMake\bin\cmake.exe")
    if ($vs) {
        $places = @((Join-Path $vs 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe')) + $places
    }
    foreach ($c in $places) {
        if (Test-Path $c) {
            $cmake = $c
            break
        }
    }
}
$install = "winget install Microsoft.VisualStudio.2022.BuildTools --override " +
           "`"--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended`""
if (-not $cmake) {
    Die "to build the game, this machine needs CMake 3.16 or later: Visual Studio's Build Tools bring one`n$install"
}

$build = Join-Path $repo 'build\run'
$configured = (Test-Path (Join-Path $build 'CMakeCache.txt')) -and
    ((Test-Path (Join-Path $build 'efz.sln')) -or (Test-Path (Join-Path $build 'build.ninja')) -or
     (Test-Path (Join-Path $build 'Makefile')))
if (-not $configured) {
    # With Visual Studio, CMake's own choice: its newest one.
    $generator = @()
    if (-not $vs) {
        if ((Have g++) -and (Have ninja)) {
            $generator = '-G', 'Ninja'
        } elseif ((Have g++) -and (Have mingw32-make)) {
            $generator = '-G', 'MinGW Makefiles'
        } else {
            Die "to build the game, this machine needs Visual Studio's C++ tools, or MinGW-w64:`n$install"
        }
    }
    & $cmake -S $repo -B $build @generator -Wno-dev
    if ($LASTEXITCODE -ne 0) {
        Die 'CMake could not set up the build (above)'
    }
}
& $cmake --build $build --config RelWithDebInfo --parallel
if ($LASTEXITCODE -ne 0) {
    Die 'the build failed (above)'
}
# Visual Studio builds each configuration into a folder of its own.
$exe = Join-Path $build 'RelWithDebInfo\efz.exe'
if (-not (Test-Path $exe)) {
    $exe = Join-Path $build 'efz.exe'
}
if (-not (Test-Path $exe)) {
    Die "the build made no efz.exe in $build"
}
if ($buildOnly) {
    Write-Output "built $exe"
    exit 0
}

# efz.exe is a windowed program: PowerShell waits for it, and what it writes to stdout
# and stderr (its errors) reaches this console, only when its output is piped.
& $exe @gameArgs 2>&1 | ForEach-Object { "$_" }
exit $LASTEXITCODE
