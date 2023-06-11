//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

// Implement method definitions here



int Rook::validMove(int to_x, int to_y){
  if (to_x < 8 && to_x >= 0 && to_y < 8 && to_y >= 0){
    int deltax = abs(this->m_x - to_x);
    int deltay = abs(this->m_y - to_y);

    if (deltax != 0 && deltay == 0){
        int directionIdentity = (to_x - this->m_x)/deltax;
        int tempx;
        for (int i = 1; i <= deltax; i++){
            tempx = this->m_x + (i*directionIdentity);
            if (tempx == to_x){
              if ((*this->m_board->state(to_y, to_x)).type() != '.' && m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()){
                return 2;
              }
              else if ((*this->m_board->state(to_y, to_x)).type() == '.'){
                return 1;
              }
            }
            else if (tempx < 8 && tempx >= 0 && (*this->m_board->state(to_y, tempx)).type() != '.'){
              return 0;
            }
        }
    }

    if (deltax == 0 && deltay != 0){
        int directionIdentity = (to_y - this->m_y)/deltay;
        int tempy;
        for (int i = 1; i <= deltay; i++){
          tempy = this->m_y + (i*directionIdentity);
          if (tempy == to_y){
            if ((*this->m_board->state(to_y, to_x)).type() != '.' && m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()){
              return 2;
            }
            else if ((*this->m_board->state(to_y, to_x)).type() == '.'){

              return 1;

            }
          }

          else if (tempy < 8 && tempy >= 0 &&(*this->m_board->state(tempy, to_x)).type() != '.') {
              return 0;
          }
        }
     }
  }
  return 0;
};

string Rook::utfRepresentation(){
  if (this->m_is_white){
    return "♖";
  }
  return "♜";
};

char Rook::latin1Representation(){
  if (this->m_is_white){
    return 'R';
  }
  return 'r';
};

bool Rook::capturingMove(int to_x, int to_y) {
    if (this -> Rook::validMove(to_x, to_y) == 2){
      return true;
    }

    return false;
}

bool Rook::nonCapturingMove(int to_x, int to_y) {
    if (this -> Rook::validMove(to_x, to_y) == 1){
      return true;
    }

    return false;
}

vector<ChessMove> Rook::capturingMoves(){
  vector<ChessMove> moves;
  for (int i = 0; i < 8; i++){
    if (this -> capturingMove(i, this->m_y)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x =  i;
      move.to_y = this->m_y;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x, i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x;
      move.to_y = i;
      move.piece = this;
      moves.push_back(move);
    }
  }
  return moves;
};

vector<ChessMove> Rook::nonCapturingMoves(){
  vector<ChessMove> moves;
  for (int i = 0; i < 8; i++){
    if (nonCapturingMove(i, this->m_y)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = i;
      move.to_y = this->m_y;
      move.piece = this;
      moves.push_back(move);
    }

    if (nonCapturingMove(this->m_x, i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x;
      move.to_y = i;
      move.piece = this;
      moves.push_back(move);
    }
  }
  return moves;

};
