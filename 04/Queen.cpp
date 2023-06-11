//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

// Implement method definitions here
Queen::Queen(int x, int y, bool is_white, ChessBoard* board)
  :ChessPiece(x, y, is_white, board)
  ,Rook(x, y, is_white, board)
  ,Bishop(x, y, is_white, board){
}

int Queen::validMove(int to_x, int to_y){
  int rValid = Rook::validMove(to_x, to_y);
  int bValid = Bishop::validMove(to_x, to_y);

  if (rValid == 2 || bValid == 2) return 2;
  if (rValid == 1 || bValid == 1) return 1;

  return 0;
};

string Queen::utfRepresentation(){
  if (ChessPiece::m_is_white){
    return "♕";
  }
  return  "♛";
};

char Queen::latin1Representation(){
  if (ChessPiece::m_is_white){
    return 'Q';
  }
  return 'q';
};



vector<ChessMove> Queen::capturingMoves(){
  vector<ChessMove> moves = Bishop::capturingMoves();
  vector<ChessMove> rookMoves = Rook::capturingMoves();
  moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());

  return moves;
};

vector<ChessMove> Queen::nonCapturingMoves(){
  vector<ChessMove> moves = Bishop::nonCapturingMoves();
  vector<ChessMove> rookMoves = Rook::nonCapturingMoves();
  moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
  return moves;
};
