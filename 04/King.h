//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
    // Override virtual methods from ChessPiece here
    public:
      using ChessPiece::ChessPiece;
      int validMove(int to_x, int to_y);
      string utfRepresentation();
      char latin1Representation();
      vector<ChessMove> capturingMoves();
      vector<ChessMove> nonCapturingMoves();
};


#endif //KING_H
