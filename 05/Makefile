CC = g++
CFLAGS = -Wall -g

all:
	python3 ../cxxtest-4.4/bin/cxxtestgen --error-printer -o myrunner.cpp testtree.cpp
	g++ -c -o bintree.o bintree.cpp
	g++ -o bintreetest_runner myrunner.cpp -I ../cxxtest-4.4 bintree.o

tests:
	./bintreetest_runner

valgrind: all balancetest
	valgrind --leak-check=full ./bintreetest_runner
	valgrind --leak-check=full ./btest.o

balancetest:
	g++ -g -o btest.o testbalance.cpp bintree.cpp
	./btest.o

clean:
	rm -f *.o *.out
