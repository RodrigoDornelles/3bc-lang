set(TCC_PATHS "${CMAKE_SOURCE_DIR}/../tcc" "${CMAKE_SOURCE_DIR}/../tinycc" "${CMAKE_SOURCE_DIR}/vendor/tcc")

if(IGNORE_PATH)
find_program(TCC tcc PATHS ${TCC_PATHS} NO_DEFAULT_PATH)
else()
find_program(TCC tcc PATHS ${TCC_PATHS})
endif()

if(NOT DEFINED CMAKE_MAKE_PROGRAM)
set(CMAKE_MAKE_PROGRAM "make")
endif()

if(NOT TCC)
    cmake_minimum_required(VERSION 3.14)
    include(FetchContent)
    FetchContent_Populate(
      vendor_tcc
      GIT_TAG "mob"
      GIT_REPOSITORY "https://github.com/C-Chads/tinycc"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/tcc"
      SUBBUILD_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_tcc_cache"
      BINARY_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/git_tcc_cache"
    )
    execute_process(
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/vendor/tcc"
      COMMAND "./configure"
      COMMAND_ERROR_IS_FATAL ANY
    )
    execute_process(
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/vendor/tcc"
      COMMAND "${CMAKE_MAKE_PROGRAM}"
      COMMAND_ERROR_IS_FATAL ANY
    )
endif()

find_program(TCC tcc PATHS ${TCC_PATHS} REQUIRED)
get_filename_component(TCC_LIBC ${TCC} DIRECTORY)
execute_process(COMMAND ${TCC} -v
  OUTPUT_VARIABLE TCC_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  COMMAND_ERROR_IS_FATAL ANY
)
