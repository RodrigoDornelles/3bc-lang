option(TEST_SIZES "Test: sizes" OFF)
option(TEST_UNIT "Test: unit" OFF)

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
    add_executable("tests_sizes_primitives" "${CMAKE_SOURCE_DIR}/tests/sizes/primitives.c")
    add_test(NAME "primitives_sizes" COMMAND "tests_sizes_primitives")
endif()

if(TEST_UNIT)
    include(CTest)
    set(tests
        "bugs_util_stoi,src/util/util_stoi.c"
        "error_util_ascii,src/util/util_ascii.c"
        "error_util_dsl_line,src/util/util_dsl.c"
        "error_util_dsl_split,src/util/util_dsl.c"
        "error_util_djb2,src/util/util_djb2.c"
        "error_util_dsl_keyword,src/util/util_dsl.c"
        "error_util_stoi2,src/util/util_stoi.c"
        "error_util_stoi8,src/util/util_stoi.c"
        "error_util_stoi10,src/util/util_stoi.c"
        "error_util_stoi16,src/util/util_stoi.c"
        "error_driver_stack,src/driver/driver_stack.c"
        "tests_util_args,src/util/util_args.c"
        "tests_util_ascii,src/util/util_ascii.c"
        "tests_util_dsl_line,src/util/util_dsl.c"
        "tests_util_dsl_split,src/util/util_dsl.c"
        "tests_util_djb2,src/util/util_djb2.c"
        "tests_util_itos2,src/util/util_itos.c"
        "tests_util_itos8,src/util/util_itos.c"
        "tests_util_itos10,src/util/util_itos.c"
        "tests_util_itos16,src/util/util_itos.c"
        "tests_util_dsl_keyword,src/util/util_dsl.c"
        "tests_util_stoi2,src/util/util_stoi.c"
        "tests_util_stoi8,src/util/util_stoi.c"
        "tests_util_stoi10,src/util/util_stoi.c"
        "tests_util_stoi16,src/util/util_stoi.c"
        "tests_util_strchr,src/util/util_strchr.c"
        "tests_driver_stack_min,src/driver/driver_stack.c"
    )
    foreach(deps IN LISTS tests)
        string(REPLACE "," ";${CMAKE_SOURCE_DIR}/" deps "${deps}")
        list(GET deps 0 tests_name)
        list(REMOVE_AT deps 0)
        add_executable("${tests_name}" "${CMAKE_SOURCE_DIR}/tests/unit/${tests_name}.c;${deps}")
        add_test(NAME "${tests_name}" COMMAND "${tests_name}")
    endforeach()
endif()
