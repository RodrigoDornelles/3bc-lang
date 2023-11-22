set(TCC_PATHS
  "${CMAKE_SOURCE_DIR}/../tcc"
  "${CMAKE_SOURCE_DIR}/../tinycc"
  "${CMAKE_SOURCE_DIR}/vendor/tcc"
  "${CMAKE_SOURCE_DIR}/../tcc/bin"
  "${CMAKE_SOURCE_DIR}/../tinycc/bin"
  "${CMAKE_SOURCE_DIR}/vendor/tcc/bin"
  "${CMAKE_SOURCE_DIR}/../tcc/lib"
  "${CMAKE_SOURCE_DIR}/../tinycc/lib"
  "${CMAKE_SOURCE_DIR}/vendor/tcc/lib"
  "${CMAKE_SOURCE_DIR}/../tcc/lib/tcc"
  "${CMAKE_SOURCE_DIR}/../tinycc/lib/tcc"
  "${CMAKE_SOURCE_DIR}/vendor/tcc/lib/tcc"
  "${CMAKE_SOURCE_DIR}/../tcc/include"
  "${CMAKE_SOURCE_DIR}/../tinycc/include"
  "${CMAKE_SOURCE_DIR}/vendor/tcc/include"
  "${CMAKE_SOURCE_DIR}/../tcc/lib/tcc/include"
  "${CMAKE_SOURCE_DIR}/../tinycc/lib/tcc/include"
  "${CMAKE_SOURCE_DIR}/vendor/tcc/lib/tcc/include"
)

if(IGNORE_PATH)
find_program(TCC tcc PATHS ${TCC_PATHS} NO_DEFAULT_PATH)
else()
find_program(TCC tcc PATHS ${TCC_PATHS})
endif()

# @todo support another system
set(TCC_DOWNLOAD "https://github.com/vlang/tccbin/archive/refs/heads/master.zip")

if(NOT TCC)
    cmake_minimum_required(VERSION 3.14)
    include(FetchContent)
    FetchContent_Populate(
      vendor_tcc
      URL "${TCC_DOWNLOAD}"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/tcc"
      SUBBUILD_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/vendor_tcc_cache"
      BINARY_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/vendor_tcc_cache"
    )
endif()

find_program(TCC tcc PATHS ${TCC_PATHS} REQUIRED)
find_file(TCC_LIBC stddef.h PATHS ${TCC_PATHS} REQUIRED)
find_file(TCC_LIBTCC libtcc.h PATHS ${TCC_PATHS} REQUIRED)
find_file(TCC_LIBAR libtcc1.a PATHS ${TCC_PATHS} REQUIRED)
get_filename_component(TCC_LIBC ${TCC_LIBC} DIRECTORY)
get_filename_component(TCC_LIBTCC ${TCC_LIBTCC} DIRECTORY)
get_filename_component(TCC_LIBAR ${TCC_LIBAR} DIRECTORY)
execute_process(COMMAND ${TCC} -v
  OUTPUT_VARIABLE TCC_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  COMMAND_ERROR_IS_FATAL ANY
)
