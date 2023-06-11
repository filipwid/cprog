//
// DD1388 - Lab 4: Losing Chess
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
  using ChessPiece::ChessPiece;
  int validMove(int to_x, int to_y);
  string utfRepresentation();
  char latin1Representation();
  vector<ChessMove> capturingMoves();
  vector<ChessMove> nonCapturingMoves();
};


#endif //PAWN_H
