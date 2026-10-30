# The native game: the recovered sources (src/) with SDL3 in place of Win32 and DirectX
# (port/), for Windows, macOS and Linux, 64-bit. The Makefile builds the original
# efz.exe; this builds the same game to run natively. See docs/native.md.
#
#   cmake -B build-native -G Ninja && cmake --build build-native
#   build-native/efz --data /path/to/EFZ
cmake_minimum_required(VERSION 3.16)
project(efz LANGUAGES C CXX)
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# SDL3: a pinned release, built with the game and linked statically, unless
# EFZ_SYSTEM_SDL3 asks for an installed one. EFZ_SDL3_ARCHIVE can point at a local copy
# of the release tarball.
option(EFZ_SYSTEM_SDL3 "Use an installed SDL3 instead of building one" OFF)
set(EFZ_SDL3_VERSION 3.4.18)
set(EFZ_SDL3_SHA256 9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3)
set(EFZ_SDL3_ARCHIVE
    "https://github.com/libsdl-org/SDL/releases/download/release-${EFZ_SDL3_VERSION}/SDL3-${EFZ_SDL3_VERSION}.tar.gz"
    CACHE STRING "SDL3 release tarball (URL or path)")
if(EFZ_SYSTEM_SDL3)
  find_package(SDL3 REQUIRED CONFIG)
else()
  include(FetchContent)
  set(SDL_SHARED OFF CACHE BOOL "" FORCE)
  set(SDL_STATIC ON CACHE BOOL "" FORCE)
  set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
  set(SDL_TESTS OFF CACHE BOOL "" FORCE)
  set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(SDL3 URL "${EFZ_SDL3_ARCHIVE}" URL_HASH SHA256=${EFZ_SDL3_SHA256})
  FetchContent_MakeAvailable(SDL3)
endif()

# sin, cos and atan2 from this CPU's x87 instead of their emulation (port/x87.cpp): the
# original's results on this machine exactly, but no longer the same on every machine.
# For the replay test on x86; GCC or Clang.
option(EFZ_HOST_X87 "Take sin, cos and atan2 from this CPU's x87" OFF)

# The game's own sources, less the four the platform layer replaces.
file(GLOB EFZ_GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
foreach(f main graphics input sound)
  list(REMOVE_ITEM EFZ_GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/${f}.cpp)
endforeach()
file(GLOB EFZ_PORT_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/port/*.cpp)

add_executable(efz WIN32 MACOSX_BUNDLE ${EFZ_GAME_SOURCES} ${EFZ_PORT_SOURCES})
target_include_directories(efz PRIVATE port src)
# EFZ_TRACE: the replay test's harness (src/trace.cpp), idle unless asked for.
target_compile_definitions(efz PRIVATE EFZ_NATIVE EFZ_TRACE)
target_link_libraries(efz PRIVATE SDL3::SDL3)
if(EFZ_HOST_X87)
  target_compile_definitions(efz PRIVATE EFZ_HOST_X87)
endif()

# The recovered code reads every structure through casts of other types, so the
# compiler may not assume the types keep apart; signed arithmetic wraps and char is
# signed, as with the original's compiler; and no multiply-add is fused, so that the
# floating point rounds where the original's did.
if(MSVC)
  target_compile_options(efz PRIVATE /utf-8 /bigobj /fp:precise /fp:contract- /W2 /wd4244 /wd4305
                                     /wd4309 /wd4146 /wd4200 /wd4838 /wd4996)
  target_compile_definitions(efz PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(efz PRIVATE -fno-strict-aliasing -fwrapv -fsigned-char
                                     -ffp-contract=off -fno-fast-math
                                     -Wno-conversion-null -Wno-narrowing
                                     $<$<CXX_COMPILER_ID:GNU>:-Wno-aggressive-loop-optimizations>)
endif()
if(MINGW)
  target_link_options(efz PRIVATE -static)
endif()

# The floating point emulation must give the same bits everywhere (tests/x87_test.cpp).
enable_testing()
add_executable(efz-x87-test tests/x87_test.cpp port/x87.cpp)
target_include_directories(efz-x87-test PRIVATE port)
target_compile_options(efz-x87-test PRIVATE
                       $<IF:$<CXX_COMPILER_ID:MSVC>,/fp:precise /fp:contract-,-ffp-contract=off>)
add_test(NAME x87 COMMAND efz-x87-test)
