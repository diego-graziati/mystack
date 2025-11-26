CC=g++
ARCHIVER=ar
INCLUDEDIR=include/

SOURCES=src/main.cpp
LIBS_DIR=lib/

MYSTACK_LIB_SOURCES=src/mystack/pthread/mystack_pthread_int.cpp
MYTEST_LIB_SOURCES=src/mytest/test_suit_tools.cpp src/mytest/pthread/mystack_test_pthread.cpp

all: build-libs
	${CC} -I ${INCLUDEDIR} -L ${LIBS_DIR} -Wall ${SOURCES} -lmytest -lmystack -o build/es_stack

build-static-mystack-lib:
	${CC} -c ${MYSTACK_LIB_SOURCES} -I ${INCLUDEDIR}
	${ARCHIVER} rcs lib/libmystack.a *.o

build-static-mytest-lib:
	rm -f *.o
	${CC} -c ${MYTEST_LIB_SOURCES} -I ${INCLUDEDIR}
	${ARCHIVER} rcs lib/libmytest.a *.o

build-libs: build-static-mystack-lib build-static-mytest-lib
	rm -f *.o

clean-docs:
	rm -rf docs/

docs: clean-docs
	doxygen config/doxygen/Doxyfile