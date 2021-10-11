CC=gcc
CXX=g++
CFLAGS=-O0
LDFLAGS=-lm
SOURCES=main.c

.PHONY: docs tests tests-clear tests-build tests-unit

all:
	##################################
	##              ##    ##        ## [3BC Language]
	##              ##    ##        ## 
	##              ##    ##    ###### Choose a target:
	############    ##    ##    ###### 
	############    ##    ##    ###### > make docs
	##              ##    ##        ## > make tests
	##              ##    ##        ## > make build
	##              ##    ############
	############    ##              ##
	############    ##              ##
	##              ##    ######    ##
	##              ##    ######    ##
	##              ##              ##
	##################################

docs:
	@rm -Rf _site/ 2>/dev/null; true
	@bundle exec jekyll serve --watch --incremental --livereload
	
build:
	@${CC} ${SOURCES} ${CFLAGS} ${LDFLAGS}

tests: tests-clear tests-build tests-unit
	@

tests-clear:
	@echo " > clearing coverage metadata..."
	@rm *.gcda *.gcno 2>/dev/null; true

tests-build:
	@echo " > building..."
	@${CXX} -Wno-deprecated -coverage unit.c ${CFLAGS} ${LDFLAGS} -o 3bc.test.bin

tests-unit:
	@echo " > run units tests..."
	@ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/*.test.rb