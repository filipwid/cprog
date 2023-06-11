//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

int ChessPiece::validMove(int to_x, int to_y) {
    return 0;
}

string ChessPiece::utfRepresentation() {
    return ".";
}

char ChessPiece::latin1Representation() {
    return '.';
}

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
    : m_x(x)
    , m_y(y)
    , m_is_white(is_white)
    , m_board(board)
    {
}


bool ChessPiece::isWhite() const {
  return m_is_white;
}

char ChessPiece::type(){
  return latin1Representation();
}

void ChessPiece::setPosition(int to_x, int to_y){
    this -> m_x = to_x;
    this -> m_y = to_y;
}

int ChessPiece::getXPosition() const {
    return m_x;
}

int ChessPiece::getYPosition() const {
    return m_y;
}

string ChessPiece::getUtf(){
  return this -> utfRepresentation();
}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    if (this -> validMove(to_x, to_y) == 2){
      return true;
    }

    return false;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    if (validMove(to_x, to_y) == 1){
      return true;
    }

    return false;
}

vector<ChessMove> ChessPiece::capturingMoves() {
  vector<ChessMove> moves;
  return moves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
  vector<ChessMove> moves;
  return moves;
}
