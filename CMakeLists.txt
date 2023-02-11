project(tbc)
cmake_minimum_required(VERSION 3.0)
include(cmake/include.cmake)
include(cmake/logo.cmake)
include(cmake/outputdir.cmake)
include(cmake/packages.cmake)


add_executable("hello" "${CMAKE_SOURCE_DIR}/programs/hello.c")
target_link_libraries("hello" tbc_cpu_no_math)
target_link_libraries("hello" tbc_legacy)
target_link_libraries("hello" tbc_interpreter)
target_link_libraries("hello" tbc_driver_no_math)
target_link_libraries("hello" tbc_bus_std)
target_link_libraries("hello" tbc_pkg_std_hello)

add_executable("3bc" "${CMAKE_SOURCE_DIR}/programs/interpreter.c")
target_link_libraries("3bc" m)
