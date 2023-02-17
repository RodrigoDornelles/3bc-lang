option(TEST_SIZES "Test: sizes" OFF)

if(DEFINED TESTS)
    if(${TESTS} MATCHES "sizes")
        set(TEST_SIZES ON)
    endif()
endif()

if(TEST_SIZES)
    include(CTest)
    add_executable("test_sizes_primitives" "${CMAKE_SOURCE_DIR}/tests/sizes/primitives.c")
    add_test(NAME "primitives_sizes" COMMAND "test_sizes_primitives")
endif()
