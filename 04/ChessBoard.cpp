//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <fstream>
ChessBoard::ChessBoard(){
    m_state = Matrix<shared_ptr<ChessPiece>> (8);
}

shared_ptr<ChessPiece> ChessBoard::state(int y, int x) {
    shared_ptr<ChessPiece> ret = m_state(y,x);
    return ret;
}

void ChessBoard::setState(int y, int x, shared_ptr<ChessPiece> piece){
    this -> m_state(y,x) = piece;
}

int ChessBoard::checkWin() {    // Flags for state with win
    vector<ChessMove> white_cap = capturingMoves(true);
    vector<ChessMove> white_non_cap = nonCapturingMoves(true);
    vector<ChessMove> black_cap = capturingMoves(false);
    vector<ChessMove> black_non_cap = nonCapturingMoves(false);

    // Win states
    if (m_white_pieces.size() == 0 || (white_cap.size() == 0 && white_non_cap.size() == 0)) return 1;
    if (m_black_pieces.size() == 0 || (black_cap.size() == 0 && black_non_cap.size() == 0)) return 2;

    // Draws
    //Draw when bishops on different color tiles exist
    if ((white_cap.size() == 0 &&  white_non_cap.size() != 0) && (black_cap.size() == 0 &&  black_non_cap.size() != 0)) {
      bool tile1 = true, tile2 = true;
      bool set_tile = false;

      for (ChessPiece * piece : m_white_pieces){
          if (piece -> nonCapturingMoves().size() > 0) {
              if (piece -> type() != 'B'){
                return 0;
              }
              if (set_tile) {

                  // If all bishops are not on the same color of tile, then the game is not over
                  if (tile1 != ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2)) {
                      return 0;
                  }
              }
              else {
                  tile1 = ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2);
                  set_tile = true;
              }

          }
          else if (piece -> type() == 'P') {
              char temp_type = state(piece -> getYPosition() - 1, piece -> getXPosition()) -> type();

              // If a pawn is blocked by something other than a opposite color pawn, the game has not yet drawn
              if (temp_type != 'p' ) return 0;

              // The pawn must be on the same color tile as the bishops
              else if (set_tile) {
                  if (tile1 != ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2)) {
                      return 0;
                  }
              }
              else {
                  tile1 = ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2);
                  set_tile = true;
              }
          }

      }

      set_tile = false;
      for (ChessPiece * piece : m_black_pieces){
          if (piece -> nonCapturingMoves().size() > 0) {
              if (piece -> type() != 'b'){
                return 0;
              }
              if (set_tile) {
                  if (tile2 != ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2)) {
                      return 0;
                  }
              }
              else {
                  tile2 = ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2);
                  set_tile = true;
              }

          }
          else if (piece -> type() == 'p') {
              char temp_type = state(piece -> getYPosition() + 1, piece -> getXPosition()) -> type();
              if (temp_type != 'P' ) {
                  return 0;
              }
              else if (set_tile) {
                  if (tile2 != ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2)) {
                      return 0;
                  }
              }
              else {
                  tile2 = ((piece -> getXPosition()) % 2 == (piece -> getYPosition()) % 2);
                  set_tile = true;
              }
          }

      }
    if (tile1 == tile2) return 0;

    return 3;
    }

    return 0;
}
void ChessBoard::movePiece(ChessMove chess_move) {
    ChessPiece * mpiece = chess_move.piece;
    int x = chess_move.to_x;
    int y = chess_move.to_y;
    if (mpiece -> validMove(x,y) != 0){
      if (mpiece -> validMove(x,y) == 2){
        removePiece(&(*m_state(y,x)));
      }

      int old_x = chess_move.from_x;
      int old_y = chess_move.from_y;
      setState(y, x, state(old_y, old_x));
      mpiece -> setPosition(x,y);
      shared_ptr<ChessPiece> square = make_shared<ChessPiece>(ChessPiece(old_x, old_y, true, this));
      setState(old_y, old_x, square);


      if ((y == 7 || y == 0) && (mpiece -> type() == 'p' || mpiece -> type() == 'P')){
        promotion(mpiece);
      }
    }
}

void ChessBoard::removePiece(ChessPiece * piece) { // I assume you'll want to clear the piece from the m_white/black_list, maybe there is a better way
    if (piece -> isWhite()) {
      for (int i = 0; i < (int)(this -> m_white_pieces.size()); i++){
        if (this -> m_white_pieces[i] == piece){
          this -> m_white_pieces.erase(m_white_pieces.begin() + i); //https://iq.opengenus.org/ways-to-remove-elements-from-vector-cpp/
        }
      }
    }
    else {
      for (int i = 0; i < (int)(this -> m_black_pieces.size()); i++){
        if (this -> m_black_pieces[i] == piece){
          this ->m_black_pieces.erase(m_black_pieces.begin() + i);
        }
      }
    }
}

void ChessBoard::promotion(ChessPiece * piece){
    int val = rand() % 5;
    bool is_white = piece -> isWhite();
    int x = piece -> getXPosition(), y = piece -> getYPosition();
    removePiece(piece);

    shared_ptr<ChessPiece> new_piece;
    if (val == 0) { // Queen promotion
      new_piece = make_shared<Queen>(x, y, is_white, this);
    }

    else if (val == 1) { // King promotion
      new_piece = make_shared<King>(x, y, is_white, this);
    }

    else if (val == 2) { // Knight promotion
        new_piece = make_shared<Knight>(x, y, is_white, this);
    }

    else if (val == 3) { // Bishop promotion
        new_piece = make_shared<Bishop>(x, y, is_white, this);
    }

    else if (val == 4) { // Rook promotion
        new_piece = make_shared<Rook>(x, y, is_white, this);
    }

    setState(y, x, new_piece);

    if (is_white){
        m_white_pieces.push_back(&(*m_state(y, x)));     // shared_ptr might cuase problems
    }
    else {
        m_black_pieces.push_back(&(*m_state(y, x)));
    }

}

void ChessBoard::addVectorPiece(ChessPiece* piece, bool is_white){
    if (is_white) {
        m_white_pieces.push_back(piece);
    }
    else {
        m_black_pieces.push_back(piece);
    }
}

vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    vector<ChessMove> moves;
    if (is_white){
        for (ChessPiece * piece : m_white_pieces){
            vector<ChessMove> piece_moves = piece -> capturingMoves();
            for (ChessMove move : piece_moves){
              moves.push_back(move);
            }
        }
    }
    else {
        for (ChessPiece * piece : m_black_pieces){
            vector<ChessMove> piece_moves = piece -> capturingMoves();
            for (ChessMove move : piece_moves){
              moves.push_back(move);
            }
        }
    }

    return moves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    vector<ChessMove> moves;
    if (is_white){
        for (ChessPiece * piece : m_white_pieces){
            vector<ChessMove> piece_moves = piece -> nonCapturingMoves();
            for (ChessMove move : piece_moves){
              moves.push_back(move);
            }
        }
    }
    else {
        for (ChessPiece * piece : m_black_pieces){
            vector<ChessMove> piece_moves = piece -> nonCapturingMoves();
            for (ChessMove move : piece_moves){
              moves.push_back(move);
            }
        }
    }

    return moves;
}

ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    string temp;
    for (int i = 0; i < 8; i++) {
        is >> temp;
        for (int j = 0; j < 8; j++) {

            if (temp[j] == 'K') { // || temp[j] == "♔"){
                shared_ptr<ChessPiece> new_piece = make_shared<King>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'k') { // || temp[j] == "♚"){
                shared_ptr<ChessPiece> new_piece = make_shared<King>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == 'Q') { // || temp[j] == "♕"){
                shared_ptr<ChessPiece> new_piece = make_shared<Queen>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'q') { // || temp[j] == "♛"){
                shared_ptr<ChessPiece> new_piece = make_shared<Queen>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == 'R') { // || temp[j] == "♖"){
                shared_ptr<ChessPiece> new_piece = make_shared<Rook>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'r') { // || temp[j] == '♜'){
                shared_ptr<ChessPiece> new_piece = make_shared<Rook>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == 'B') { // || temp[j] == "♗"){
                shared_ptr<ChessPiece> new_piece = make_shared<Bishop>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'b') { // || temp[j] == "♝"){
                shared_ptr<ChessPiece> new_piece = make_shared<Bishop>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == 'N') { // || temp[j] == "♘"){
                shared_ptr<ChessPiece> new_piece = make_shared<Knight>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'n') { // || temp[j] == "♞"){
                shared_ptr<ChessPiece> new_piece = make_shared<Knight>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == 'P') { // || temp[j] == "♙"){
                shared_ptr<ChessPiece> new_piece = make_shared<Pawn>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), true);
            }
            else if (temp[j] == 'p') { // || temp[j] == "♟"){
                shared_ptr<ChessPiece> new_piece = make_shared<Pawn>(j, i, false, &cb);
                cb.setState(i, j, new_piece);
                cb.addVectorPiece(&(*new_piece), false);
            }
            else if (temp[j] == '.'){
                shared_ptr<ChessPiece> new_piece = make_shared<ChessPiece>(j, i, true, &cb);
                cb.setState(i, j, new_piece);
            }
        }
    }

    return cb;
}

ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            os << cb.state(i,j) -> getUtf();
        }
        os << endl;
    }

    return cb;
}


void ChessBoard::randomThinkerAI(bool is_white) { // Makes a move for stated color, based on lab instructions
    vector<ChessMove> capturing = capturingMoves(is_white);
    vector<ChessMove> non_capturing = nonCapturingMoves(is_white);
    ChessMove move;

    // Requires a rand seed to be set beforehand
    if (capturing.size() > 0) {
        int val = rand() % capturing.size();
        move = capturing[val];
        this -> movePiece(move);
    }
    else {
        if (non_capturing.size() != 0) {
          int val = rand() % non_capturing.size();
          move = non_capturing[val];
          this -> movePiece(move);
        }
    }
}

void ChessBoard::thinkingAI(bool is_white) { // Makes a move for stated color, based on lab instructions
    vector<ChessMove> capturing = capturingMoves(is_white);
    vector<ChessMove> non_capturing = nonCapturingMoves(is_white);
    vector<ChessMove> op_capturing = capturingMoves(!is_white);
    vector<ChessMove> op_non_capturing = nonCapturingMoves(!is_white);

    ChessMove move;
    if (capturing.size() == 0) {
        for (ChessMove m1 : non_capturing) {
            int move_x = m1.to_x;
            int move_y = m1.to_y;

            for (ChessMove m2 : op_non_capturing) {
                if (move_x == m2.to_x && move_y == m2.to_y && m2.piece -> type() != 'p' && m2.piece -> type() != 'P'){
                    this -> moveThinkingAI(m1);
                    return;
                }
                else if (m2.piece -> type() == 'p' || m2.piece -> type() == 'P') {
                    if (move_y == m2.to_y && abs(move_x - m2.to_x) == 1){
                        this -> moveThinkingAI(m1);
                        return;
                    }
                }
              }
            }
            // If the code makes it here, then no non_capturing move that would force a capturing move for the opponent was found
            if (non_capturing.size() != 0) {
                int val = rand() % non_capturing.size();
                move = non_capturing[val];
                this -> moveThinkingAI(move);
            }
    }
    else {
        for (ChessMove m1 : capturing) {
            int move_x = m1.to_x;
            int move_y = m1.to_y;
            for (ChessMove m2 : op_non_capturing) {
                if (move_x == m2.to_x && move_y == m2.to_y && m1.piece -> type() != 'p' && m1.piece -> type() != 'P'){
                    this -> moveThinkingAI(m1);
                    return;
                }
                else if (m2.piece -> type() == 'p' || m2.piece -> type() == 'P') {
                    if (move_x == m2.to_x && abs(move_y - m2.to_y) < 2 && abs(m2.from_x - m2.to_x) == 1){
                        this -> moveThinkingAI(m1);
                        return;
                    }
                }
            }
          }
        // If the code makes it here, then no non_capturing move that would force a capturing move for the opponent was found
        if (capturing.size() != 0) {

          int val = rand() % capturing.size();
          move = capturing[val];
          this -> moveThinkingAI(move);
        }
        return;
    }
}

void ChessBoard::moveThinkingAI(ChessMove move) {
    if ((move.to_y == 7 || move.to_y == 0) && (move.piece -> type() == 'p' || move.piece -> type() == 'P')){
        bool is_white = move.piece -> isWhite();
        int x = move.to_x, y = move.to_y;

        for (int i = 0; i < 5; i++) {
            shared_ptr<ChessPiece> new_piece;

            if (i == 0) { // Queen promotion
              new_piece = make_shared<Queen>(x, y, is_white, this);
            }

            else if (i == 1) { // King promotion
              new_piece = make_shared<King>(x, y, is_white, this);
            }

            else if (i == 2) { // Knight promotion
                new_piece = make_shared<Knight>(x, y, is_white, this);
            }

            else if (i == 3) { // Bishop promotion
                new_piece = make_shared<Bishop>(x, y, is_white, this);
            }

            else if (i == 4) { // Rook promotion
                new_piece = make_shared<Rook>(x, y, is_white, this);
            }
            if (new_piece -> capturingMoves().size() == 0) {
                if (state(y, x) -> type() != '.') {
                    removePiece(&(*m_state(y,x)));
                }
                removePiece(move.piece);
                setState(move.to_y, move.to_x, new_piece);
                shared_ptr<ChessPiece> square = make_shared<ChessPiece>(ChessPiece(move.from_x, move.from_y, true, this));
                setState(move.from_y, move.from_x, square);

                if (is_white){
                    m_white_pieces.push_back(&(*m_state(y, x)));
                }
                else {
                    m_black_pieces.push_back(&(*m_state(y, x)));
                }

                return;
            }
        }
    }
    this -> movePiece(move);
}
