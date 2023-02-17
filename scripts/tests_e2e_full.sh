echo " > running full tests suite...\n"
ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/e2e/*.*.rb
