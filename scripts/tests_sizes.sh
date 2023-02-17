cmake . -DTEST_SIZES=ON
make test_sizes_primitives
ctest . --output-on-failure
