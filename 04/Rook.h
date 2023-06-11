//
// DD1388 - Lab 4: Losing Chess
//

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : virtual public ChessPiece {
public:
  using ChessPiece::ChessPiece;
  int validMove(int to_x, int to_y);
  string utfRepresentation();
  char latin1Representation();
  vector<ChessMove> capturingMoves();
  vector<ChessMove> nonCapturingMoves();
  bool capturingMove(int to_x, int to_y);
  bool nonCapturingMove(int to_x, int to_y);
};


#endif //ROOK_H
