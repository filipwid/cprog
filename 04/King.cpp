//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"

// Implement method definitions here

int King::validMove(int to_x, int to_y){
  if (to_x < 8 && to_x >= 0 && to_y < 8 && to_y >= 0){
    int deltax = abs(this->m_x - to_x);
    int deltay = abs(this->m_y - to_y);
    if (deltax*deltay == 1 || deltax + deltay){
      if ((*this->m_board->state(to_y, to_x)).type() != '.' && m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()) {
        return 2;
      }
      if ((*this->m_board->state(to_y, to_x)).type() == '.'){
        return 1;
      }
    }
  }
  return 0;
};

string King::utfRepresentation(){
  if (this->m_is_white){
    return "♔";
  }
  return "♚";
};

char King::latin1Representation(){
  if (this->m_is_white){
    return 'K';
  }
  return 'k';
};



vector<ChessMove> King::capturingMoves(){
  vector<ChessMove> moves;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if (capturingMove(this->m_x + i, this->m_y + j)){
        ChessMove move;
        move.from_x = this -> m_x;
        move.from_y = this -> m_y;
        move.to_x = this->m_x + i;
        move.to_y = this->m_y + j;
        move.piece = this;
        moves.push_back(move); // https://cplusplus.com/reference/vector/vector/ Push back seems like the most valid insert method
      }
    }
  }
  return moves;
};

vector<ChessMove> King::nonCapturingMoves(){
  vector<ChessMove> moves;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if (nonCapturingMove(this->m_x + i, this->m_y + j)){
        ChessMove move;
        move.from_x = this -> m_x;
        move.from_y = this -> m_y;
        move.to_x = this->m_x + i;
        move.to_y = this->m_y + j;

        move.piece = this;
        moves.push_back(move);
      }
    }
  }
  return moves;

};
