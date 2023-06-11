//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <fstream>
#include <vector>
#include <istream>
#include <memory>
#include "ChessMove.h"
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h

using namespace std;

class ChessPiece;

class ChessBoard {
    // add additional members or functions of your choice

private:
    // Alternative 1 (the matrix owns the chess pieces):
    Matrix<shared_ptr<ChessPiece>> m_state; // Matrix from lab 2
    vector<ChessPiece *> m_white_pieces;
    vector<ChessPiece *> m_black_pieces;

    // Alternative 2 (the vectors own the chess pieces):
    // Matrix<ChessPiece *> m_state; // Matrix from lab 2
    // vector<shared_ptr<ChessPiece>> m_white_pieces;
    // vector<shared_ptr<ChessPiece>> m_black_pieces;

    void removePiece(ChessPiece * piece);

    void promotion(ChessPiece * piece);
public:
    ChessBoard();
    void movePiece(ChessMove chess_move);
    void addVectorPiece(ChessPiece* piece, bool is_white);
    void setState(int x, int y, shared_ptr<ChessPiece> piece);
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);
    shared_ptr<ChessPiece> state(int x, int y);
    void randomThinkerAI(bool is_white);
    void thinkingAI(bool is_white);
    int checkWin();
    void moveThinkingAI(ChessMove move);
};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);



#endif //CHESSBOARD_H
