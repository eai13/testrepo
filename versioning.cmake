# defines GIT_TAG_NAME, GIT_TAG_SHA, GIT_TAG_TIMESTAMP

if (NOT DEFINED ENV{TAG_NAME})
    message(WARNING "TAG_NAME is not defined")
endif()

if (NOT DEFINED ENV{TAG_SHA})
    message(WARNING "TAG_SHA is not defined")
endif()

if (DEFINED ENV{TAG_TIMESTAMP})
    message(WARNING "TAG_TIMESTAMP is not defined")
endif()

set(GIT_TAG_NAME  "$ENV{TAG_NAME}")
set(GIT_TAG_SHA  "$ENV{TAG_SHA}")
set(GIT_TAG_TIMESTAMP "$ENV{TAG_TIMESTAMP}")

if (NOT GIT_TAG_NAME OR
    NOT GIT_TAG_SHA OR
    NOT GIT_TAG_TIMESTAMP)
    find_program(GIT_EXEC git)
    if (NOT GIT_EXEC)
        message(WARNING "Git not found, no build metadata available")
        set(GIT_TAG_NAME "N/A")
        set(GIT_TAG_SHA "N/A")
        set(GIT_TAG_TIMESTAMP "N/A")
    else()
        execute_process(
            COMMAND ${GIT_EXEC} describe --tags --abbrev=0
            OUTPUT_VARIABLE _tag
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        execute_process(
            COMMAND ${GIT_EXEC} rev-parse HEAD
            OUTPUT_VARIABLE _sha
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        execute_process(
            COMMAND ${GIT_EXEC} log -1 --format=%cI
            OUTPUT_VARIABLE _date
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        set(GIT_TAG_NAME  "${_tag}")
        set(GIT_TAG_SHA  "${_sha}")
        set(GIT_TAG_TIMESTAMP "${_date}")
    endif()
endif()

message(STATUS "Build metadata: TAG=${GIT_TAG_NAME}, SHA=${GIT_TAG_SHA}, TIMESTAMP=${GIT_TAG_TIMESTAMP}")
