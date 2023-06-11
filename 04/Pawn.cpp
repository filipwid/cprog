//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

// Implement method definitions here

int Pawn::validMove(int to_x, int to_y){
  if (to_x < 8 && to_x >= 0 && to_y < 8 && to_y >= 0){
    if ((!(this -> isWhite())  && to_y > this -> m_y) || (this -> isWhite()  && to_y < this -> m_y)){
      int deltax = abs(this->m_x - to_x);
      int deltay = abs(this->m_y - to_y);

      if (deltay == 1 && deltax == 0){
        if ((*this->m_board->state(to_y, to_x)).type() == '.'){
          return 1;
        }
      }

      else if (deltay == 1 && deltax == 1){
        if ((*this->m_board->state(to_y, to_x)).type() != '.' && m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()) {
          return 2;
        }
      }

      else if (deltay == 2 && deltax == 0 && ((!(this -> isWhite()) && (this -> m_y == 1)) || ((this -> isWhite() && (this -> m_y == 6))))) {
        if ((*this->m_board->state(to_y, to_x)).type() == '.') {

          // Chech square infront of the pawn before the second square
          if (!this -> isWhite() && (*this->m_board->state(to_y - 1, to_x)).type() == '.') {
            return 1;
          }
          else if (this -> isWhite() && (*this->m_board->state(to_y + 1, to_x)).type() == '.') {
            return 1;
          }
        }
      }
    }
  }

  return 0;
};

string Pawn::utfRepresentation(){
  if (this->m_is_white){
    return "♙";
  }
  return "♟";
};

char Pawn::latin1Representation(){
  if (this->m_is_white){
    return 'P';
  }
  return 'p';
};



vector<ChessMove> Pawn::capturingMoves(){
  vector<ChessMove> moves;
  int addx = 1;
  int addy;
  if (this -> isWhite()) {
    addy = -1;
  }
  else {
    addy = 1;
  }
  if (capturingMove(this->m_x, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (capturingMove(this->m_x + addx, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + addx;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (capturingMove(this->m_x - addx, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - addx;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (capturingMove(this->m_x, this->m_y + 2*addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  return moves;
};

vector<ChessMove> Pawn::nonCapturingMoves(){
  vector<ChessMove> moves;
  int addx = 1;
  int addy;
  if (this -> isWhite()) {
    addy = -1;
  }
  else {
    addy = 1;
  }

  if (nonCapturingMove(this->m_x, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x + addx, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + addx;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x - addx, this->m_y + addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - addx;
    move.to_y = this->m_y + addy;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x, this->m_y + 2*addy)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x;
    move.to_y = this->m_y + 2*addy;
    move.piece = this;
    moves.push_back(move);
  }
  return moves;

};
