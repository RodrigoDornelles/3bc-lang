if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
    set(TARGET "msvc")
elseif(NOT TARGET)
    set(TARGET "native")
endif()

option(IGNORE_PATH "Not use default $$PATH" "OFF")

if(${TARGET} MATCHES "cc65-(.+)")
    set(CC65_TARGET ${CMAKE_MATCH_1})
    set(I18N_LANG "no-ne" CACHE STRING "")
    include("${CMAKE_SOURCE_DIR}/cmake/find/cc65.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/system/cc65.cmake")
    include(${CMAKE_SOURCE_DIR}/cmake/force.cmake)
    set(CMAKE_C_FLAGS "-t ${CC65_TARGET} ${CMAKE_C_FLAGS}")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain/cc65.cmake")
    message("-- using cc65 cross compiler.\n")
elseif(${TARGET} MATCHES "zcc-(.+)")
    set(ZCCTARGET "${CMAKE_MATCH_1}")
    set(I18N_LANG "no-ne" CACHE STRING "")
    include("${CMAKE_SOURCE_DIR}/cmake/find/zcc.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/system/zcc.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/force.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain/zcc.cmake")
    message("-- using z88dk cross compiler.\n")
elseif(${TARGET} MATCHES "zig-(.+)-(.+)-(.+)")
    set(ZIG_ARCH ${CMAKE_MATCH_1})
    set(ZIG_SYSTEM ${CMAKE_MATCH_2})
    set(ZIG_ABI ${CMAKE_MATCH_3})
    set(ZIG_TARGET "${ZIG_ARCH}-${ZIG_SYSTEM}-${ZIG_ABI}")
    include("${CMAKE_SOURCE_DIR}/cmake/find/zig.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/system/zig.cmake")
    include(${CMAKE_SOURCE_DIR}/cmake/force.cmake)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain/zig.cmake")
    message("-- using zig cross compiler.")
elseif(${TARGET} MATCHES "tcc")
    include("${CMAKE_SOURCE_DIR}/cmake/find/tcc.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain/tcc.cmake")
    message("-- using tcc fast compiler.")
elseif(${TARGET} STREQUAL msvc)
    message("-- using msvc native compiler.")
    set(MSVC TRUE)
elseif(${TARGET} STREQUAL native)
    unset(CMAKE_TOOLCHAIN_FILE)
    message("-- using host native compiler.")
    message("-- NOTE: for distribution use '-DTARGET=<compiler>-<system>-<arch>-<abi>'\n")
else()
    message(FATAL_ERROR "target '${TARGET}' its not supported at the moment." )
endif()
