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
    set(tests
        "error_driver_stack,src/driver/driver_stack.c"
        "error_cast_stoi2,src/cast/cast_stoi.c"
        "error_cast_stoi8,src/cast/cast_stoi.c"
        "test_cast_itos2,src/cast/cast_itos.c"
        "test_cast_itos8,src/cast/cast_itos.c"
        "test_cast_itos10,src/cast/cast_itos.c"
        "test_cast_itos16,src/cast/cast_itos.c"
        "test_cast_stoi2,src/cast/cast_stoi.c"
        "test_cast_stoi8,src/cast/cast_stoi.c"
        "test_driver_stack_min,src/driver/driver_stack.c"
    )
    foreach(deps IN LISTS tests)
        string(REPLACE "," ";${CMAKE_SOURCE_DIR}/" deps "${deps}")
        list(GET deps 0 test_name)
        list(REMOVE_AT deps 0)
        add_executable("${test_name}" "${CMAKE_SOURCE_DIR}/tests/unit/${test_name}.c;${deps}")
        add_test(NAME "${test_name}" COMMAND "${test_name}")
    endforeach()
endif()
