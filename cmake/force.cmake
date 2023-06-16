if(DEFINED CMAKE_SYSTEM_VERSION)
    set(CONIO FALSE)
    set(WIN32 FALSE)
    set(APPLE FALSE)
    set(LINUX FALSE)
    set(UNIX FALSE)

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "nes")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".nes")
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "c64")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".prg")
        set(CONIO TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "atari5200")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".bin")
        set(CONIO TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "pce")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".bin")
        set(CONIO TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "msx")
        set(CONIO TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "pet")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".prg")
        set(CONIO TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "windows")
        set(CMAKE_EXECUTABLE_SUFFIX_C ".exe")
        set(WIN32 TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "linux")
        set(LINUX TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "darwin")
        set(APPLE TRUE)
        set(POSIX TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} STREQUAL "macos")
        set(APPLE TRUE)
        set(POSIX TRUE)
    endif()

    if(${CMAKE_SYSTEM_VERSION} MATCHES "bsd")
        set(UNIX TRUE)
        set(POSIX TRUE)
    endif()
endif()
