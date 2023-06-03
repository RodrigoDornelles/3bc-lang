function(tbc_size)
    string(TOUPPER "${ARGV1}" LEN1)
    if(DEFINED CMAKE_SYSTEM_VERSION)
        if("${CMAKE_SYSTEM_VERSION}" STREQUAL "pce")
            if("${LEN1}" STREQUAL "32K")
                set_target_properties("${ARGV0}" PROPERTIES LINK_FLAGS "-Wl -D__CARTSIZE__=0x8000")
            endif()
            if("${LEN1}" STREQUAL "16K")
                set_target_properties("${ARGV0}" PROPERTIES LINK_FLAGS "-Wl -D__CARTSIZE__=0x4000")
            endif()
            if("${LEN1}" STREQUAL "8K")
                set_target_properties("${ARGV0}" PROPERTIES LINK_FLAGS "-Wl -D__CARTSIZE__=0x2000")
            endif()
        endif()
    endif()
endfunction()
