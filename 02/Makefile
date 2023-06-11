CC = g++
CFLAGS = -Wall -g
testgen:
	python3 ../cxxtest-4.4/bin/cxxtestgen --error-printer -o myrunner.cpp mytest.h
	g++ -o runner myrunner.cpp -I ../cxxtest-4.4
	./runner

valgrind:
	valgrind --leak-check=full ./runner


clean:
	rm -f *.o *.out
