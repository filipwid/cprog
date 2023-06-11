//
// DD1388 - Lab 4: Losing Chess
//
#include <unistd.h>
#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <sstream>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string.h>

// Implement additional functions or classes of your choice
using std::vector; using std::stringstream; using std::cout; using std::endl;
void game(istream &is, char *argv[]) {
    srand(time(NULL));

    string line;
    ChessBoard chess;

    // Read board
    stringstream board_ss;
    for (size_t i = 0; i < 8; ++i) {
        if (!std::getline(is, line)) {
            throw runtime_error("Could not read board.");
        }
        board_ss << line << endl; //.substr(0, 8);
    }
    board_ss >> chess;
    
    // Command line arguments
    // First command is what ai white will use, second is what ai black will use and third is who goes first

    // Both smart ai, white goes first, ex ./main smart smart white < test.in
    if (strcmp(argv[1], "smart") == 0 && strcmp(argv[2], "smart") == 0 && strcmp(argv[3], "white") == 0){
      cout << chess;
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.thinkingAI(true);
        cout << chess;
        cout << endl;
        chess.thinkingAI(false);
        }
    }
    else if (strcmp(argv[1], "smart") == 0 && strcmp(argv[2], "smart") == 0 && strcmp(argv[3], "black") == 0){
      cout << chess;
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.thinkingAI(false);
        cout << chess;
        cout << endl;
        chess.thinkingAI(true);
        }
    }
    else if (strcmp(argv[1], "random") == 0 && strcmp(argv[2], "smart") == 0 && strcmp(argv[3], "white") == 0){
      cout << chess;
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(true);
        cout << chess;
        cout << endl;
        chess.thinkingAI(false);
        }
    }
    else if (strcmp(argv[1], "random") == 0 && strcmp(argv[2], "smart") == 0 && strcmp(argv[3], "black") == 0){
      cout << chess;
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.thinkingAI(false);
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(true);
        }
    }
    else if (strcmp(argv[1], "smart") == 0 && strcmp(argv[2], "random") == 0 && strcmp(argv[3], "white") == 0){
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.thinkingAI(true);
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(false);

        }
    }
    else if (strcmp(argv[1], "smart") == 0 && strcmp(argv[2], "random") == 0 && strcmp(argv[3], "black") == 0){
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(false);
        cout << chess;
        cout << endl;
        chess.thinkingAI(true);
        }
    }
    else if (strcmp(argv[1], "random") == 0 && strcmp(argv[2], "random") == 0 && strcmp(argv[3], "white") == 0){
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(true);
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(false);
        }
    }
    else if (strcmp(argv[1], "random") == 0 && strcmp(argv[2], "random") == 0 && strcmp(argv[3], "black") == 0){
      while (chess.checkWin() == 0) {
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(false);
        cout << chess;
        cout << endl;
        chess.randomThinkerAI(true);
        }
    }

    else {
      cout << "Invalid command line options" << endl << "Valid command line options example: smart smart white < test.in" << endl;
    }
}

int main(int argc, char *argv[]) {
  try {
      // Test boards from stdin
      if (!cin.eof() && argc == 4) {
          game(cin, argv);
      }
      else {
        cout << "Invalid command line options" << endl << "Valid command line options example: smart smart white < test.in" << endl;
      }
  } catch (std::runtime_error & error) {
      cerr << error.what() << endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
  }
