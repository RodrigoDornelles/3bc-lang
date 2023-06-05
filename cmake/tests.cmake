option(TEST_SIZES "Test: sizes" OFF)
option(TEST_SIZES "Test: unit" OFF)

if(DEFINED TESTS)
    if(${TESTS} MATCHES "sizes")
        set(TEST_SIZES ON)
    endif()
    if(${TESTS} MATCHES "unit")
        set(TEST_UNIT ON)
    endif()
endif()

if(TEST_SIZES)
    include(CTest)
    add_executable("test_sizes_primitives" "${CMAKE_SOURCE_DIR}/tests/sizes/primitives.c")
    add_test(NAME "primitives_sizes" COMMAND "test_sizes_primitives")
endif()

if(TEST_UNIT)
    include(CTest)
    add_executable("test_cast_itos2" "${CMAKE_SOURCE_DIR}/tests/unit/test_cast_itos2.c")
    target_link_libraries("test_cast_itos2" "tbc_cast")
    add_test(NAME "test_cast_itos2" COMMAND "test_cast_itos2")
    add_executable("test_cast_itos10" "${CMAKE_SOURCE_DIR}/tests/unit/test_cast_itos10.c")
    target_link_libraries("test_cast_itos10" "tbc_cast")
    add_test(NAME "test_cast_itos10" COMMAND "test_cast_itos10")
    add_executable("test_cast_itos16" "${CMAKE_SOURCE_DIR}/tests/unit/test_cast_itos16.c")
    target_link_libraries("test_cast_itos16" "tbc_cast")
    add_test(NAME "test_cast_itos16" COMMAND "test_cast_itos16")
    add_executable("test_cast_itos8" "${CMAKE_SOURCE_DIR}/tests/unit/test_cast_itos8.c")
    target_link_libraries("test_cast_itos8" "tbc_cast")
    add_test(NAME "test_cast_itos8" COMMAND "test_cast_itos8")
    add_executable("error_driver_stack"
        "${CMAKE_SOURCE_DIR}/tests/unit/error_driver_stack.c"
        "${CMAKE_SOURCE_DIR}/src/driver/driver_stack.c"
    )
    add_test(NAME "error_driver_stack" COMMAND "error_driver_stack")
    add_executable("test_driver_stack_min"
        "${CMAKE_SOURCE_DIR}/tests/unit/test_driver_stack_min.c"
        "${CMAKE_SOURCE_DIR}/src/driver/driver_stack.c"
    )
    add_test(NAME "test_driver_stack_min" COMMAND "test_driver_stack_min")
endif()
