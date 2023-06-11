CC = g++
CFLAGS = -Wall -g

all:
	python3 ../cxxtest-4.4/bin/cxxtestgen --error-printer -o myrunner.cpp complextest.h
	g++ -c -o Complex.o Complex.cpp
	g++ -o complextest_runner myrunner.cpp -I ../cxxtest-4.4 Complex.o

tests:
	./complextest_runner
clean:
	rm -f *.o *.out
