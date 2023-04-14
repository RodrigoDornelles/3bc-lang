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

