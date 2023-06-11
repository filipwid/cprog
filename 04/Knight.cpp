//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"

int Knight::validMove(int to_x, int to_y){
  if (to_x < 8 && to_x >= 0 && to_y < 8 && to_y >= 0){
    int deltax = abs(this->m_x - to_x);
    int deltay = abs(this->m_y - to_y);
    if (deltax*deltax + deltay*deltay == 5){
      if ((*this->m_board->state(to_y, to_x)).type() != '.' && m_is_white != (*this -> m_board -> state(to_y, to_x)).isWhite()){
        return 2;
      }
      if ((*this->m_board->state(to_y, to_x)).type() == '.'){
        return 1;
      }
    }
  }
  return 0;
};

string Knight::utfRepresentation(){
  if (this->m_is_white){
    return "♘";
  }
  return "♞";
};

char Knight::latin1Representation(){
  if (this->m_is_white){
    return 'N';
  }
  return 'n';
};

vector<ChessMove> Knight::capturingMoves(){
  vector<ChessMove> moves;
    if (capturingMove(this->m_x + 1, this->m_y + 2)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + 1;
      move.to_y = this->m_y + 2;
      move.piece = this;
      moves.push_back(move);
    }


    if (capturingMove(this->m_x + 2, this->m_y + 1)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + 2;
      move.to_y = this->m_y + 1;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x - 1, this->m_y + 2)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - 1;
      move.to_y = this->m_y + 2;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x - 2, this->m_y + 1)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - 2;
      move.to_y = this->m_y + 1;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x + 1, this->m_y - 2)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + 1;
      move.to_y = this->m_y - 2;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x + 2, this->m_y - 1)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x + 2;
      move.to_y = this->m_y - 1;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x - 1, this->m_y - 2)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - 1;
      move.to_y = this->m_y - 2;
      move.piece = this;
      moves.push_back(move);
    }

    if (capturingMove(this->m_x - 2, this->m_y - 1)){
      ChessMove move;
      move.from_x = this -> m_x;
      move.from_y = this -> m_y;
      move.to_x = this->m_x - 2;
      move.to_y = this->m_y - 1;
      move.piece = this;
      moves.push_back(move);
    }

  return moves;
};

vector<ChessMove> Knight::nonCapturingMoves(){
  vector<ChessMove> moves;
  if (nonCapturingMove(this->m_x + 1, this->m_y + 2)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + 1;
    move.to_y = this->m_y + 2;
    move.piece = this;
    moves.push_back(move);
  }


  if (nonCapturingMove(this->m_x + 2, this->m_y + 1)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + 2;
    move.to_y = this->m_y + 1;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x - 1, this->m_y + 2)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - 1;
    move.to_y = this->m_y + 2;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x - 2, this->m_y + 1)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - 2;
    move.to_y = this->m_y + 1;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x + 1, this->m_y - 2)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + 1;
    move.to_y = this->m_y - 2;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x + 2, this->m_y - 1)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x + 2;
    move.to_y = this->m_y - 1;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x - 1, this->m_y - 2)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - 1;
    move.to_y = this->m_y - 2;
    move.piece = this;
    moves.push_back(move);
  }

  if (nonCapturingMove(this->m_x - 2, this->m_y - 1)){
    ChessMove move;
    move.from_x = this -> m_x;
    move.from_y = this -> m_y;
    move.to_x = this->m_x - 2;
    move.to_y = this->m_y - 1;
    move.piece = this;
    moves.push_back(move);
  }

  return moves;
};
