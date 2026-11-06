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
# layer's parts every build shares; and SDL3's, with the game's log, crash reports and
# fight records (docs/logging.md).
file(GLOB EFZ_GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
foreach(f main graphics input sound)
  list(REMOVE_ITEM EFZ_GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/${f}.cpp)
endforeach()
set(EFZ_PORT_SOURCES)
foreach(f arena graphics layout win32 x87)
  list(APPEND EFZ_PORT_SOURCES ${CMAKE_SOURCE_DIR}/port/${f}.cpp)
endforeach()
set(EFZ_SDL_SOURCES)
foreach(f main sdlmain input sound video log crash record)
  list(APPEND EFZ_SDL_SOURCES ${CMAKE_SOURCE_DIR}/port/${f}.cpp)
endforeach()
# Netplay: EfzRevival 1.02h's, built in (port/netplay/, docs/netplay.md).
foreach(f net protocol session titleitem netplay)
  list(APPEND EFZ_SDL_SOURCES ${CMAKE_SOURCE_DIR}/port/netplay/${f}.cpp)
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
  # The crash report's stack traces and minidumps (port/crash.cpp); netplay's sockets and
  # the host's network adapters.
  if(WIN32)
    target_link_libraries(efz PRIVATE dbghelp ws2_32 iphlpapi)
  else()
    target_link_libraries(efz PRIVATE ${CMAKE_DL_LIBS})
  endif()
  # The revision and configuration the log names (port/log.cpp), from git at each build.
  add_custom_target(efz-buildinfo
    COMMAND ${CMAKE_COMMAND} -DSOURCE=${CMAKE_SOURCE_DIR} -DOUT=${CMAKE_BINARY_DIR}/efz_build.h
            -P ${CMAKE_SOURCE_DIR}/tools/buildinfo.cmake
    BYPRODUCTS ${CMAKE_BINARY_DIR}/efz_build.h
    VERBATIM)
  add_dependencies(efz efz-buildinfo)
  target_include_directories(efz PRIVATE ${CMAKE_BINARY_DIR})
  target_compile_definitions(efz PRIVATE EFZ_BUILD_CONFIG="$<CONFIG>")
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
  # On Linux the arena's base pointers take the static TLS model (EFZ_THREAD_LOCAL,
  # port/guest.h), and only they.
  if(MSVC)
    target_compile_options(efz_headless PRIVATE $<$<NOT:$<CONFIG:Debug>>:/Ob2 /Oi /GL>)
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

# Netplay's network layer and EfzRevival's rand (tests/netplay_test.cpp): zlib, protobuf's
# wire format, the random numbers both sides draw, a socket over the loopback. No game
# data and no peer.
add_executable(efz-netplay-test tests/netplay_test.cpp port/netplay/net.cpp port/x87.cpp)
target_include_directories(efz-netplay-test PRIVATE port)
target_compile_options(efz-netplay-test PRIVATE
                       $<IF:$<CXX_COMPILER_ID:MSVC>,/fp:precise /fp:contract-,-ffp-contract=off>)
if(WIN32)
  target_link_libraries(efz-netplay-test PRIVATE ws2_32 iphlpapi)
endif()
add_test(NAME netplay COMMAND efz-netplay-test)

# A crash or a hang must leave a report (port/crash.cpp, docs/logging.md): the game
# crashes or hangs on purpose, which needs no game data.
if(EFZ_GAME)
  foreach(kind segv abort fatal hang)
    add_test(NAME crash-${kind}
             COMMAND ${CMAKE_COMMAND} -DEFZ=$<TARGET_FILE:efz> -DKIND=${kind}
                     -DDIR=${CMAKE_BINARY_DIR}/crash-test-${kind}
                     -P ${CMAKE_SOURCE_DIR}/tests/crash_test.cmake)
  endforeach()
endif()

# What the headless library relies on, checked without the game's data (labelled
# headless: ctest -L headless). The game itself is the compatibility suite's, which
# tools/compat.py runs in both the game and efz-headless.
if(EFZ_HEADLESS)
  add_executable(efz-headless-test tests/headless_test.cpp $<TARGET_OBJECTS:efz_headless>)
  efz_game_target(efz-headless-test)
  target_include_directories(efz-headless-test PRIVATE ${CMAKE_SOURCE_DIR}/port/headless)
  target_compile_definitions(efz-headless-test PRIVATE EFZ_MULTI_INSTANCE EFZ_ENV_BUILD)
  target_link_libraries(efz-headless-test PRIVATE Threads::Threads)
  if(MSVC)
    target_link_options(efz-headless-test PRIVATE $<$<NOT:$<CONFIG:Debug>>:/LTCG>)
  endif()
  if(MINGW)
    target_link_options(efz-headless-test PRIVATE -static)
  endif()
  if(EFZ_COVERAGE)
    target_link_options(efz-headless-test PRIVATE --coverage)
  endif()
  add_test(NAME headless COMMAND efz-headless-test)
  # The Python package against the library (skipped without numpy).
  find_package(Python3 COMPONENTS Interpreter QUIET)
  if(Python3_Interpreter_FOUND)
    add_test(NAME headless-python
             COMMAND Python3::Interpreter -m unittest discover -s python/tests -t python -v
             WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    set_tests_properties(headless-python PROPERTIES LABELS headless
                         ENVIRONMENT "EFZ_ENV_LIBRARY=$<TARGET_FILE:efz_env>")
  endif()
  set_tests_properties(headless PROPERTIES LABELS headless)
endif()
