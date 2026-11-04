# The native game: the recovered sources (src/) with SDL3 in place of Win32 and DirectX
# (port/), for Windows, macOS and Linux, 64-bit. The Makefile builds the original
# efz.exe; this builds the same game to run natively. See docs/native.md.
#
# The same sources also build headless (port/headless/, docs/headless.md): efz_env, a
# library that runs batches of games on all cores without a window or sound, for
# training agents; efz-headless, the game run that way for the compatibility test; and
# efz-bench. -DEFZ_GAME=OFF builds only those, without SDL3.
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

option(EFZ_GAME "Build the game (needs SDL3)" ON)
option(EFZ_HEADLESS "Build the headless library and tools (port/headless/)" ON)

# SDL3: a pinned release, built with the game and linked statically, unless
# EFZ_SYSTEM_SDL3 asks for an installed one. EFZ_SDL3_ARCHIVE can point at a local copy
# of the release tarball.
option(EFZ_SYSTEM_SDL3 "Use an installed SDL3 instead of building one" OFF)
set(EFZ_SDL3_VERSION 3.4.18)
set(EFZ_SDL3_SHA256 9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3)
set(EFZ_SDL3_ARCHIVE
    "https://github.com/libsdl-org/SDL/releases/download/release-${EFZ_SDL3_VERSION}/SDL3-${EFZ_SDL3_VERSION}.tar.gz"
    CACHE STRING "SDL3 release tarball (URL or path)")
if(EFZ_GAME)
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
endif()

# sin, cos and atan2 from this CPU's x87 instead of their emulation (port/x87.cpp): the
# original's results on this machine exactly, but no longer the same on every machine.
# For the replay test on x86; GCC or Clang.
option(EFZ_HOST_X87 "Take sin, cos and atan2 from this CPU's x87" OFF)

# Line coverage (gcov) of the game, for `tools/compat.py coverage`: what the
# compatibility test's cases run. GCC or Clang.
option(EFZ_COVERAGE "Instrument the game for gcov" OFF)

# The game's own sources, less the four the platform layer replaces; the platform
# layer's parts every build shares; and SDL3's.
file(GLOB EFZ_GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
foreach(f main graphics input sound)
  list(REMOVE_ITEM EFZ_GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/${f}.cpp)
endforeach()
set(EFZ_PORT_SOURCES)
foreach(f arena graphics layout win32 x87)
  list(APPEND EFZ_PORT_SOURCES ${CMAKE_SOURCE_DIR}/port/${f}.cpp)
endforeach()
set(EFZ_SDL_SOURCES)
foreach(f main sdlmain input sound video)
  list(APPEND EFZ_SDL_SOURCES ${CMAKE_SOURCE_DIR}/port/${f}.cpp)
endforeach()

# What every target compiling the game needs. The recovered code reads every structure
# through casts of other types, so the compiler may not assume the types keep apart;
# signed arithmetic wraps and char is signed, as with the original's compiler; and no
# multiply-add is fused, so that the floating point rounds where the original's did.
# EFZ_TRACE: the replay test's harness (src/trace.cpp), idle unless asked for.
function(efz_game_target target)
  target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/port ${CMAKE_SOURCE_DIR}/src)
  target_compile_definitions(${target} PRIVATE EFZ_NATIVE EFZ_TRACE)
  if(EFZ_HOST_X87)
    target_compile_definitions(${target} PRIVATE EFZ_HOST_X87)
  endif()
  if(EFZ_COVERAGE)
    target_compile_options(${target} PRIVATE --coverage)
  endif()
  if(MSVC)
    target_compile_options(${target} PRIVATE /utf-8 /bigobj /fp:precise /fp:contract- /W2 /wd4244
                                             /wd4305 /wd4309 /wd4146 /wd4200 /wd4838 /wd4996)
    target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS)
  else()
    target_compile_options(${target} PRIVATE -fno-strict-aliasing -fwrapv -fsigned-char
                                             -ffp-contract=off -fno-fast-math
                                             -Wno-conversion-null -Wno-narrowing
                                             $<$<CXX_COMPILER_ID:GNU>:-Wno-aggressive-loop-optimizations>)
  endif()
endfunction()

if(EFZ_GAME)
  add_executable(efz WIN32 MACOSX_BUNDLE ${EFZ_GAME_SOURCES} ${EFZ_PORT_SOURCES} ${EFZ_SDL_SOURCES})
  efz_game_target(efz)
  target_link_libraries(efz PRIVATE SDL3::SDL3)
  if(EFZ_COVERAGE)
    target_link_options(efz PRIVATE --coverage)
  endif()
  if(MINGW)
    target_link_options(efz PRIVATE -static)
  endif()
endif()

# The headless library: the game compiled once more, each game in an arena of its own
# (EFZ_MULTI_INSTANCE), with the headless platform in place of SDL3's. Built for speed:
# fully inlined, and on MSVC with link-time code generation.
if(EFZ_HEADLESS)
  set(EFZ_HEADLESS_SOURCES
      ${CMAKE_SOURCE_DIR}/port/headless/platform.cpp
      ${CMAKE_SOURCE_DIR}/port/headless/env.cpp)
  add_library(efz_headless OBJECT ${EFZ_GAME_SOURCES} ${EFZ_PORT_SOURCES} ${EFZ_HEADLESS_SOURCES})
  efz_game_target(efz_headless)
  target_include_directories(efz_headless PRIVATE ${CMAKE_SOURCE_DIR}/port/headless)
  target_compile_definitions(efz_headless PRIVATE EFZ_MULTI_INSTANCE EFZ_ENV_BUILD)
  set_target_properties(efz_headless PROPERTIES POSITION_INDEPENDENT_CODE ON
                                                CXX_VISIBILITY_PRESET hidden
                                                VISIBILITY_INLINES_HIDDEN ON)
  if(MSVC)
    target_compile_options(efz_headless PRIVATE $<$<NOT:$<CONFIG:Debug>>:/Ob2 /Oi /GL>)
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # The arena's base is thread-local (port/guest.h) and read on every pointer the game
    # follows: the static TLS model, not a __tls_get_addr call each time. Two pointers
    # fit in what glibc keeps for libraries loaded later.
    target_compile_options(efz_headless PRIVATE -ftls-model=initial-exec)
  endif()

  # efz_env: the C API of port/headless/efz_env.h, for Python (python/efz_env) and
  # anything else. Its operator new is the arena's and stays its own: on Linux the
  # library binds its own symbols and exports only efz_env_*.
  add_library(efz_env SHARED $<TARGET_OBJECTS:efz_headless>)
  target_include_directories(efz_env INTERFACE ${CMAKE_SOURCE_DIR}/port/headless)
  find_package(Threads REQUIRED)
  target_link_libraries(efz_env PRIVATE Threads::Threads)
  if(MSVC)
    target_link_options(efz_env PRIVATE $<$<NOT:$<CONFIG:Debug>>:/LTCG>)
  elseif(APPLE)
    target_link_options(efz_env PRIVATE -Wl,-exported_symbol,_efz_env_*)
  else()
    file(WRITE ${CMAKE_BINARY_DIR}/efz_env.map "{ global: efz_env_*; local: *; };\n")
    target_link_options(efz_env PRIVATE -Wl,-Bsymbolic -Wl,--version-script=${CMAKE_BINARY_DIR}/efz_env.map)
  endif()
  if(MINGW)
    target_link_options(efz_env PRIVATE -static)
  endif()

  # efz-headless: the game on the headless platform, for tools/compat.py.
  add_executable(efz-headless ${CMAKE_SOURCE_DIR}/port/headless/runner.cpp $<TARGET_OBJECTS:efz_headless>)
  efz_game_target(efz-headless)
  target_compile_definitions(efz-headless PRIVATE EFZ_MULTI_INSTANCE EFZ_ENV_BUILD)
  target_link_libraries(efz-headless PRIVATE Threads::Threads)
  if(MSVC)
    target_link_options(efz-headless PRIVATE $<$<NOT:$<CONFIG:Debug>>:/LTCG>)
  endif()
  if(MINGW)
    target_link_options(efz-headless PRIVATE -static)
  endif()
  if(EFZ_COVERAGE)
    target_link_options(efz_env PRIVATE --coverage)
    target_link_options(efz-headless PRIVATE --coverage)
  endif()

  # efz-bench: speed and determinism of efz_env.
  add_executable(efz-bench ${CMAKE_SOURCE_DIR}/port/headless/bench.cpp)
  target_link_libraries(efz-bench PRIVATE efz_env)
  if(MINGW)
    target_link_options(efz-bench PRIVATE -static)
  endif()
endif()

# The floating point emulation must give the same bits everywhere (tests/x87_test.cpp).
enable_testing()
add_executable(efz-x87-test tests/x87_test.cpp port/x87.cpp)
target_include_directories(efz-x87-test PRIVATE port)
target_compile_options(efz-x87-test PRIVATE
                       $<IF:$<CXX_COMPILER_ID:MSVC>,/fp:precise /fp:contract-,-ffp-contract=off>)
add_test(NAME x87 COMMAND efz-x87-test)
