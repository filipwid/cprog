CC = g++
CFLAGS = -Wall -g

hello: main.cpp hello.o
	$(CC) $(FLAGS) main.cpp hello.o -o hello

hello.o: hello.cpp
	$(CC) $(FLAGS) -c hello.cpp

clean:
	rm -f *.o *.out
