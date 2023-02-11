project(tbc)
cmake_minimum_required(VERSION 3.0)
include(cmake/logo.cmake)
include(cmake/outputdir.cmake)


add_executable("hello" "${CMAKE_SOURCE_DIR}/programs/hello.c")
target_link_libraries(hello m)
