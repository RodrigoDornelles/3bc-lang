add_library(tbc_pkg_std_hello OBJECT "${CMAKE_SOURCE_DIR}/src/pkg/pkg_std_hello.c")
add_library(tbc_pkg_std_lang OBJECT "${CMAKE_SOURCE_DIR}/src/pkg/pkg_std_lang.c")

# Standard Virtual Machine (CPU)
FILE(GLOB tbc_cpu_std_files "${CMAKE_SOURCE_DIR}/src/cpu/*.c")
add_library(tbc_cpu_std OBJECT ${tbc_cpu_std_files})
add_library(tbc_cpu_no_math OBJECT ${tbc_cpu_std_files})
target_compile_definitions("tbc_cpu_no_math" PRIVATE TBC_NOT_MATH)

# Bus
FILE(GLOB tbc_bus_std_files "${CMAKE_SOURCE_DIR}/src/bus/*.c")
add_library(tbc_bus_std OBJECT ${tbc_bus_std_files})

# System dependencies
FILE(GLOB tbc_sys_std_files "${CMAKE_SOURCE_DIR}/src/sys/sys_common_*.c")
if(UNIX OR LINUX)
FILE(GLOB tbc_sys_posix_files "${CMAKE_SOURCE_DIR}/src/sys/sys_posix_*.c")
set(tbc_sys_std_files "${tbc_sys_std_files};${tbc_sys_posix_files}")
endif()
if(DEFINED CC65_TARGET)
file(GLOB "tbc_sys_${CC65_TARGET}_files" "${CMAKE_SOURCE_DIR}/src/sys/sys_${CC65_TARGET}_*.c")
set(tbc_sys_std_files "${tbc_sys_std_files};${tbc_sys_${CC65_TARGET}_files}")
endif()

add_library(tbc_sys_std OBJECT ${tbc_sys_std_files})

# Drivers
FILE(GLOB tbc_driver_std_files "${CMAKE_SOURCE_DIR}/src/driver/*.c")
add_library(tbc_driver_std OBJECT ${tbc_driver_std_files})
add_library(tbc_driver_no_math OBJECT ${tbc_driver_std_files})
target_compile_definitions("tbc_driver_no_math" PRIVATE TBC_NOT_MATH)

# Interpreter
FILE(GLOB tbc_interpreter_files "${CMAKE_SOURCE_DIR}/src/interpreter/*.c")
add_library(tbc_interpreter OBJECT ${tbc_interpreter_files})

# Legacy
FILE(GLOB tbc_legacy_files "${CMAKE_SOURCE_DIR}/src/legacy/*.c")
add_library(tbc_legacy OBJECT ${tbc_legacy_files})