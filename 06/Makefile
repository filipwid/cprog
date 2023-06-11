CC = g++
CFLAGS = -Wall -g

all:
	$(CC) $(FLAGS) lambda.cpp -o lambda.out
	$(CC) $(FLAGS) pointers.cpp -o pointers.out
	$(CC) $(FLAGS) WaterManager.cpp -o WaterManager.out -lpthread

valgrind: all
	valgrind --leak-check=full ./lambda.out
	valgrind --leak-check=full ./pointers.out
	valgrind --leak-check=full ./WaterManager.out

silent:
	./WaterManager.out

trace:
	./WaterManager.out -trace

clean:
	rm -f *.o *.out
