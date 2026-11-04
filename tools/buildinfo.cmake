# Writes the header naming the revision the game is built from, for its log
# (port/log.cpp): cmake -DSOURCE=<checkout> -DOUT=<header> -P tools/buildinfo.cmake.
# CMakeLists.txt runs it on every build; the header changes only with the revision.
set(revision "unknown")
set(dirty 0)
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --short=12 HEAD
                  WORKING_DIRECTORY "${SOURCE}" OUTPUT_VARIABLE out RESULT_VARIABLE status
                  OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
  if(status EQUAL 0 AND out)
    set(revision "${out}")
    # Changes to tracked files, not counting the build's own.
    execute_process(COMMAND "${GIT_EXECUTABLE}" status --porcelain --untracked-files=no
                    WORKING_DIRECTORY "${SOURCE}" OUTPUT_VARIABLE changes ERROR_QUIET)
    if(changes)
      set(dirty 1)
    endif()
  endif()
endif()
set(text "// Written by tools/buildinfo.cmake.\n#define EFZ_BUILD_REVISION \"${revision}\"\n#define EFZ_BUILD_DIRTY ${dirty}\n")
file(WRITE "${OUT}.tmp" "${text}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OUT}.tmp" "${OUT}")
file(REMOVE "${OUT}.tmp")
