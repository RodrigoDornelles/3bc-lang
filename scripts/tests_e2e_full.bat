@echo off
echo " > running full tests suite...\n"
ruby.exe -Ilib -e 'ARGV.each { |f| require f }' ./tests/e2e/*.*.rb
