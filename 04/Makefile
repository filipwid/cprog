CC = g++
CFLAGS = -Wall -g
OBJFILES = main.o ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o
OBJTFILES = maint.o ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o

comp: ${OBJFILES}
	${CC} ${CFLAGS} ${OBJFILES} -o runner

compt: ${OBJTFILES}
	${CC} ${CFLAGS} ${OBJTFILES} -o runner

valgrind:
	valgrind --track-origins=yes --gen-suppressions=yes --leak-check=full ./runner

test:
	./runner < tests.in

all: clean comp

testall: clean compt test

clean:
	rm -f *.o *.out


main.o: ChessBoard.h
		${CC} ${CFLAGS} -c -o main.o main.cpp
maint.o: ChessBoard.h
		${CC} ${CFLAGS} -c -o maint.o tests.cpp
ChessPiece.o: ChessBoard.h
		${CC} ${CFLAGS} -c -o ChessPiece.o ChessPiece.cpp
ChessBoard.o:
		${CC} ${CFLAGS} -c -o ChessBoard.o ChessBoard.cpp
King.o: King.h
		${CC} ${CFLAGS} -c -o King.o King.cpp
Knight.o: Knight.h
		${CC} ${CFLAGS} -c -o Knight.o Knight.cpp
Pawn.o: Pawn.h
		${CC} ${CFLAGS} -c -o Pawn.o Pawn.cpp
Rook.o: Rook.h
		${CC} ${CFLAGS} -c -o Rook.o Rook.cpp
Bishop.o: Bishop.h
		${CC} ${CFLAGS} -c -o Bishop.o Bishop.cpp
Queen.o: Queen.h Bishop.h Rook.h
		${CC} ${CFLAGS} -c -o Queen.o Queen.cpp
