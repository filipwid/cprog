//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"


class Queen : public Rook, public Bishop {
public:
    Queen(int x, int y, bool is_white, ChessBoard* board);
    int validMove(int to_x, int to_y);
    string utfRepresentation();
    char latin1Representation();
    vector<ChessMove> capturingMoves();
    vector<ChessMove> nonCapturingMoves();
};


#endif //QUEEN_H
