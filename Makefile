.PHONY: docs tests

CXX_SOURCES ?= main/unit.c
CC_SOURCES ?= main/interpreter.c
CC_OUTPUT ?= 3bc
CC_FLAGS ?= -Os
CC_OBJECTS ?= $(CC_SOURCES:.c=.o)
LD_FLAGS ?= -lc -lm
ifdef CC_LD_TARGET
CC_TARGET := $(CC_LD_TARGET)
LD_TARGET := $(CC_LD_TARGET)
endif
ifdef CC_LD
CC := ${CC_LD}
LD := ${CC_LD}
endif
ifdef CC_TARGET
CC_TARGET_PREFIX := $(addprefix -target , ${CC_TARGET})
endif
ifdef LD_TARGET
LD_TARGET_PREFIX := $(addprefix -target , ${LD_TARGET})
endif
ifdef ZIP
ZIP_COMMAND := zip ${ZIP}  ${CC_OUTPUT} && make clean-build
endif
ifdef TAR
ZIP_COMMAND := tar -czf ${TAR}.tar.gz ${CC_OUTPUT} && make clean-build
endif

all:
	##################################
	##              ##    ##        ## [3BC Language]
	##              ##    ##        ## 
	##              ##    ##    ###### Choose a target:
	############    ##    ##    ###### 
	############    ##    ##    ###### > make build
	##              ##    ##        ## > make tests
	##              ##    ##        ## > make clean
	##              ##    ############ > make docs
	############    ##              ##
	############    ##              ##
	##              ##    ######    ##
	##              ##    ######    ##
	##              ##              ##
	##################################

build:
	(${CC} ${CC_FLAGS} ${CC_TARGET_PREFIX} -c ${CC_SOURCES} -o ${CC_OBJECTS}) || (make clean-objects && false)
	(${LD} ${CC_OBJECTS} ${LD_TARGET_PREFIX} ${LD_FLAGS} -o ${CC_OUTPUT}) || (make clean-objects && false)
	${ZIP_COMMAND}
	make clean-objects

docs: clean-docs
	@cd docs && jekyll build

docs-serve: clean-docs
	@cd docs && bundle exec jekyll serve --watch --livereload
	
clean: clean-zip clean-objects clean-build clean-test clean-docs clean-test
	@echo done!

clean-objects:
	@rm -f *.o *.obj src/*.o src/*.obj main/*.o main/*.obj 2>/dev/null; true

clean-build:
	@rm -f *.bin *.out *.s *.bin *.exe *.a *.so *.dylib *.wasm *.js *.html 3bc main unit 2>/dev/null; true

clean-zip:
	@rm -f *.zip *.tar *.tar.* 2>/dev/null; true

clean-docs:
	@rm -Rf docs/_site/* 2>/dev/null; true

clean-test:
	@rm *.gcda *.gcno 2>/dev/null; true

tests: clean-test
	@echo " > running fasts tests...\n > to use the full test suite, run: make tests-full\n"
	@${CXX} -w -coverage ${CXX_SOURCES} -O0 -lm -o 3bc.test.bin
	@ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/fasttest.*.rb

tests-full: clean-test
	@echo " > running full tests suite...\n"
	@${CXX} -w -coverage ${CXX_SOURCES} -O0 -lm -o 3bc.test.bin
	@ruby -Ilib -e 'ARGV.each { |f| require f }' ./tests/*.*.rb
