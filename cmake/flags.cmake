if(NOT DEFINED CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 90)
endif()

if(NOT DEFINED OPT)
    set(OPT "s")
endif()

if(OPT)
    add_compile_options("-O${OPT}")
endif()

if(${TARGET} STREQUAL msvc)
    if (NOT "11 17 23" MATCHES ${CMAKE_C_STANDARD})
        set(CMAKE_C_STANDARD 11)
        message("-- NOTE: forced ISO C 11 standard.")
    endif()
    add_compile_options("/std:c${CMAKE_C_STANDARD}")
endif()

if(NOT DEFINED VERSION_EXTRA)
    execute_process(
        COMMAND git log -1 --format=%h
        RESULT_VARIABLE TMP
        OUTPUT_VARIABLE VERSION_EXTRA
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NOT TMP)
        execute_process(
            COMMAND git status --porcelain
            OUTPUT_VARIABLE TMP
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if (TMP)
            set(VERSION_EXTRA "dirty-${VERSION_EXTRA}")
        endif()
    else()
        set(VERSION_EXTRA "compiled")
    endif()
    unset(TMP)
endif()

if (VERSION_EXTRA)
    add_compile_options("-DVERSION_EXTRA=\" (${VERSION_EXTRA})\\n\"")
endif()

if (ZIG_VERSION)
    add_compile_options("-DTBC_COMPILER_NICKNAME=\"zig ${ZIG_VERSION}\"")
endif()
