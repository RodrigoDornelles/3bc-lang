.PHONY: docs tests

all:
	##################################
	##              ##    ##        ## [3BC Language]
	##              ##    ##        ## 
	##              ##    ##    ###### Choose a target:
	############    ##    ##    ###### 
	############    ##    ##    ###### > make docs
	##              ##    ##        ## > make tests
	##              ##    ##        ## > make clean
	##              ##    ############
	############    ##              ##
	############    ##              ##
	##              ##    ######    ##
	##              ##    ######    ##
	##              ##              ##
	##################################

docs: clean-docs
	@cd docs && jekyll build

docs-serve: clean-docs
	@cd docs && bundle exec jekyll serve --watch --livereload
	
clean: clean-build clean-test clean-docs clean-test
	@echo done!

clean-build:
	@rm -f *.bin *.out *.s *.bin *.exe *.o *.a *.so *.dylib *.wasm *.js *.html 3bc main unit 2>/dev/null; true

clean-docs:
	@rm -Rf docs/_site/* 2>/dev/null; true

clean-test:
	@rm *.gcda *.gcno 2>/dev/null; true

tests: clean-test
	@echo " > running fasts tests...\n > to use the full test suite, run: make tests-full\n"
	@${CXX} -w -coverage main.c -O0 -lm -o 3bc.test.bin
	@ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/fasttest.*.rb

tests-full: clean-test
	@echo " > running full tests suite...\n"
	@${CXX} -w -coverage unit.c -O0 -lm -o 3bc.test.bin
	@ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/*.*.rb
