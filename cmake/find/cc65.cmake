set(CC65_PATHS "${CMAKE_SOURCE_DIR}/../cc65/bin" "${CMAKE_SOURCE_DIR}/vendor/cc65/bin")
find_program(CC65 cc65 PATHS ${CC65_PATHS})

if(NOT CC65)
    cmake_minimum_required(VERSION 3.14)
    include(FetchContent)
    FetchContent_Populate(
      vendor_cc65
      GIT_REPOSITORY "https://github.com/cc65/cc65.git"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/cc65"
      SUBBUILD_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_cc65_cache"
      BINARY_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_cc65_cache"
    )
    execute_process(
      COMMAND ${CMAKE_MAKE_PROGRAM} -C "${CMAKE_SOURCE_DIR}/vendor/cc65"
      COMMAND_ERROR_IS_FATAL ANY
    )
endif()

find_program(AR65 ar65 PATHS ${CC65_PATHS} REQUIRED)
find_program(CL65 cl65 PATHS ${CC65_PATHS} REQUIRED)
find_program(CC65 cc65 PATHS ${CC65_PATHS} REQUIRED)
