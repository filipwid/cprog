//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
  using ChessPiece::ChessPiece;
  int validMove(int to_x, int to_y);
  string utfRepresentation();
  char latin1Representation();
  vector<ChessMove> capturingMoves();
  vector<ChessMove> nonCapturingMoves();
};


#endif //KNIGHT_H
