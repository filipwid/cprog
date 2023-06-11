//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

int Bishop::validMove(int to_x, int to_y){
  if (to_x < 8 && to_x >= 0 && to_y < 8 && to_y >= 0){
    int deltax = abs(this->m_x - to_x);
    int deltay = abs(this->m_y - to_y);

    if (deltax == deltay && deltax != 0){
        int directionIdentityX = (to_x - this->m_x)/deltax;
        int directionIdentityY = (to_y - this->m_y)/deltay;
        for (int i = 1; i <= deltax; i++){
          if ((this->m_x + (i*directionIdentityX) == to_x) && (this->m_y + (i*directionIdentityY) == to_y)){

            if ((*this->m_board->state(to_y, to_x)).type() != '.'){
              if (m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()){
                return 2;
              }
            }
            else {
              return 1;
            }
          }
          else if ((*this->m_board->state(this->m_y + (i*directionIdentityY), this->m_x + (i*directionIdentityX))).type() != '.'){
            return 0;
          }
        }
    }
  }
  return 0;
};

string Bishop::utfRepresentation(){
  if (this->m_is_white){
    return "♗";
  }
  return "♝";
};

char Bishop::latin1Representation(){
  if (this->m_is_white){
    return 'B';
  }
  return 'b';
};

bool Bishop::capturingMove(int to_x, int to_y) {
    if (this -> Bishop::validMove(to_x, to_y) == 2){
      return true;
    }

    return false;
}

bool Bishop::nonCapturingMove(int to_x, int to_y) {
    if (this -> Bishop::validMove(to_x, to_y) == 1){
      return true;
    }

    return false;
}

vector<ChessMove> Bishop::capturingMoves(){
  vector<ChessMove> moves;
  int curX = this -> m_x;
  int curY = this -> m_y;
  for (int i = 1; i < 8; i++){
    if (capturingMove(curX + i, curY + i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + i;
      move.to_y = this->m_y + i;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(curX - i, curY + i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - i;
      move.to_y = this->m_y + i;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(curX + i, curY - i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + i;
      move.to_y = this->m_y - i;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(curX - i, curY - i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - i;
      move.to_y = this->m_y - i;
      move.piece = this;
      moves.push_back(move);
    }

  }
  return moves;
};

vector<ChessMove> Bishop::nonCapturingMoves(){
  vector<ChessMove> moves;
  int curX = this -> m_x;
  int curY = this -> m_y;
  for (int i = 1; i < 8; i++){
    if (nonCapturingMove(curX + i, curY + i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + i;
      move.to_y = this->m_y + i;
      move.piece = this;
      moves.push_back(move);
    }

    if (nonCapturingMove(curX - i, curY + i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - i;
      move.to_y = this->m_y + i;
      move.piece = this;
      moves.push_back(move);
    }

    if (nonCapturingMove(curX + i, curY - i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + i;
      move.to_y = this->m_y - i;
      move.piece = this;
      moves.push_back(move);
    }

    if (nonCapturingMove(curX - i, curY - i)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - i;
      move.to_y = this->m_y - i;
      move.piece = this;
      moves.push_back(move);
    }
  }
  return moves;

};
