# Standard Virtual Machine (CPU)
FILE(GLOB tbc_cpu_std_files "${CMAKE_SOURCE_DIR}/src/cpu/*.c")
add_library(tbc_cpu_std OBJECT ${tbc_cpu_std_files})
add_library(tbc_cpu_no_math OBJECT ${tbc_cpu_std_files})
add_library(tbc_cpu_hello OBJECT "${CMAKE_SOURCE_DIR}/src/cpu/cpu_string.c")
target_compile_definitions("tbc_cpu_hello" PRIVATE TBC_NOT_MATH)
target_compile_definitions("tbc_cpu_no_math" PRIVATE TBC_NOT_MATH)

# Alu
add_library(tbc_alu_std OBJECT "${CMAKE_SOURCE_DIR}/src/alu/alu_math.c")
add_library(tbc_alu_no_math OBJECT "${CMAKE_SOURCE_DIR}/src/alu/alu_math.c")
target_compile_definitions("tbc_alu_no_math" PRIVATE TBC_NOT_MATH)
add_library(tbc_alu_none OBJECT "${CMAKE_SOURCE_DIR}/src/alu/alu_none.c")

# Bus
FILE(GLOB tbc_bus_lang_files "${CMAKE_SOURCE_DIR}/src/bus/bus_*_lang.c")
FILE(GLOB tbc_bus_hello_files "${CMAKE_SOURCE_DIR}/src/bus/bus_*_hello.c")
add_library(tbc_bus_lang OBJECT "${tbc_bus_lang_files}")
add_library(tbc_bus_hello OBJECT "${tbc_bus_hello_files}")

# utility dependencies
FILE(GLOB tbc_util_files "${CMAKE_SOURCE_DIR}/src/util/*.c")
add_library(tbc_util OBJECT ${tbc_util_files})

# Datastruct dependencies
FILE(GLOB tbc_ds_array_files "${CMAKE_SOURCE_DIR}/src/ds/*.c")
add_library(tbc_array_simple OBJECT ${tbc_ds_array_files})

# System dependencies
FILE(GLOB tbc_sys_std_files "${CMAKE_SOURCE_DIR}/src/sys/sys_common_*.c")
if(UNIX OR LINUX OR APPLE)
FILE(GLOB tbc_sys_posix_files "${CMAKE_SOURCE_DIR}/src/sys/sys_posix_*.c")
set(tbc_sys_std_files "${tbc_sys_std_files};${tbc_sys_posix_files}")
endif()
IF (WIN32)
FILE(GLOB tbc_sys_windows_files "${CMAKE_SOURCE_DIR}/src/sys/sys_windows_*.c")
set(tbc_sys_std_files "${tbc_sys_std_files};${tbc_sys_windows_files}")
ENDIF()
IF (CONIO)
FILE(GLOB tbc_sys_conio_files "${CMAKE_SOURCE_DIR}/src/sys/sys_conio_*.c")
set(tbc_sys_std_files "${tbc_sys_std_files};${tbc_sys_conio_files}")
ENDIF()
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

# Internationalization
set(I18N_LANG "en-us" CACHE STRING "")
set(I18N_PATH "${CMAKE_SOURCE_DIR}/src/i18n" CACHE STRING "")
add_library(tbc_i18n OBJECT "${I18N_PATH}/i18n_${I18N_LANG}.c")

# Interpreter
FILE(GLOB tbc_interpreter_lang_files "${CMAKE_SOURCE_DIR}/src/interpreter/*.c")
list(REMOVE_ITEM tbc_interpreter_lang_files "${CMAKE_SOURCE_DIR}/src/interpreter/interpreter_mock.c")
add_library(tbc_interpreter_lang OBJECT ${tbc_interpreter_lang_files})
add_library(tbc_interpreter_none OBJECT "${CMAKE_SOURCE_DIR}/src/interpreter/interpreter_mock.c")
FILE(GLOB tbc_lang_3bc_files "${CMAKE_SOURCE_DIR}/src/lang/lang_3bc_*.c")
add_library(tbc_lang3bc OBJECT ${tbc_lang_3bc_files})

# Legacy
FILE(GLOB tbc_legacy_files "${CMAKE_SOURCE_DIR}/src/legacy/*.c")
add_library(tbc_legacy OBJECT ${tbc_legacy_files})