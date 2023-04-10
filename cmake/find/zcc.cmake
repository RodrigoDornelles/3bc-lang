set(ZCC_PATHS_BIN
    "${CMAKE_SOURCE_DIR}/../z88dk/bin"
    "${CMAKE_SOURCE_DIR}/vendor/z88dk/bin"
)
set(ZCC_PATHS_CFG "${CMAKE_SOURCE_DIR}/../z88dk/lib/config"
    "${CMAKE_SOURCE_DIR}/vendor/z88dk/lib/config"
    "/usr/local/share/z88dk/lib/config"
)

find_program(ZCC zcc PATHS ${ZCC_PATHS_BIN})

if(NOT ZCC)
    cmake_minimum_required(VERSION 3.14)
    include(FetchContent)
    FetchContent_Populate(
      vendor_zcc
      GIT_REPOSITORY "https://github.com/z88dk/z88dk"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/z88dk"
      SUBBUILD_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_z88dk_cache"
      BINARY_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_z88dk_cache"
    )
    execute_process(
      COMMAND "${CMAKE_SOURCE_DIR}/vendor/z88dk/build.sh"
      COMMAND_ERROR_IS_FATAL ANY
    )
endif()

find_program(ZCC zcc PATHS ${ZCC_PATHS_BIN} REQUIRED)
find_file(TEMP z80.cfg PATHS ${ZCC_PATHS_CFG} REQUIRED)
string(REGEX MATCH "(.+)/zcc" TMP "${ZCC}")
set(BIN_PATH "${CMAKE_MATCH_1}")
string(REGEX MATCH "(.+)/z80.cfg" TMP "${TEMP}")
set(CFG_PATH "${CMAKE_MATCH_1}" CACHE STRING "")
unset(TEMP)
