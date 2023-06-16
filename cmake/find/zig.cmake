include(cmake/uname.cmake)
set(ZIG_VERSION "0.9.1")
set(ZIG_DOWNLOAD "http://ziglang.org/download")
set(ZIG_PATHS "${CMAKE_SOURCE_DIR}/vendor/zig")

if(IGNORE_PATH)
find_program(ZIG zig PATHS ${ZIG_PATHS} NO_DEFAULT_PATH)
else()
find_program(ZIG zig PATHS ${ZIG_PATHS})
endif()

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    set(ZIG_DOWNLOAD "${ZIG_DOWNLOAD}/${ZIG_VERSION}/zig-macos-${CMAKE_HOST_SYSTEM_PROCESSOR_AARCH64}-${ZIG_VERSION}.tar.xz")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ZIG_DOWNLOAD "${ZIG_DOWNLOAD}/${ZIG_VERSION}/zig-linux-${CMAKE_HOST_SYSTEM_PROCESSOR_AARCH64}-${ZIG_VERSION}.tar.xz")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(ZIG_DOWNLOAD "${ZIG_DOWNLOAD}/${ZIG_VERSION}/zig-windows-${CMAKE_HOST_SYSTEM_PROCESSOR_AARCH64}-${ZIG_VERSION}.zip")
endif()

if(NOT ZIG)
    cmake_minimum_required(VERSION 3.14)
    include(FetchContent)
    FetchContent_Populate(
      vendor_zig
      URL "${ZIG_DOWNLOAD}"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/zig"
      SUBBUILD_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/vendor_zig_cache"
      BINARY_DIR "${CMAKE_SOURCE_DIR}/CMakeFiles/vendor_zig_cache"
    )
endif()

find_program(ZIG zig PATHS ${ZIG_PATHS} REQUIRED)
