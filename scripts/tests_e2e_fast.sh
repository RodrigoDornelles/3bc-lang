echo " > running fasts tests...\n > to use the full test suite, run: make tests-full\n"
ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/e2e/fasttest.*.rb
