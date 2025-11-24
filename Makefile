CC=g++
ARCHIVER=ar
INCLUDEDIR=include/

SOURCES=src/mytest/test_suit_tools.cpp src/mystack/mystack.cpp src/test_mystack.cpp src/main.cpp
LIBS_DIR=lib/

STACK_LIB_SOURCES=mystack.cpp
TEST_LIB_SOURCES=test_suit_tools.cpp

all:
	${CC} ${SOURCES} -I ${INCLUDEDIR} -Wall -o build/es_stack

build-static-mystack-lib:
	${CC} -c ${STACK_LIB_SOURCES} -I ${INCLUDEDIR} -o mystack.o
	${ARCHIVER} rcs libmystack.a mystack.o

build-static-mytest-lib:
	${CC} -c ${TEST_LIB_SOURCES} -I ${INCLUDEDIR} -o mytest.o
	${ARCHIVER} rcs libmytest.a mytest.o

build-libs: build-static-mystack-lib build-static-mytest-lib
	rm -f *.o

clean-docs:
	rm -rf docs/

docs: clean-docs
	doxygen config/doxygen/Doxyfile