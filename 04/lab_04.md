# Lab 4 Chesspieces, AI and Losing chess

Implement classes for Knight, Pawn, Rook, Bishop, Queen and  King. Each of these classes should inherit from 
_class Chesspiece_

If you are unsure about the rules, please [read up on them on Wikipedia](https://en.wikipedia.org/wiki/Rules_of_chess). 
For the purposes of this lab, you can skip castling ("Rockad" in Swedish), 
en passant and moves that place the king in check.

## Questions to answer

Put questions and answers in a file _inquiry.md_ and do put relevant code examples if needed for clarity.

#### What did you learn from this assignment?

#### What was most difficult to do in this assignment?

#### The code relies on virtual functions. Could the code have been written without virtual functions?

#### Could ChessPiece have been an abstract class? 

#### There was no separate unit test for each function in this assignment, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?

#### What is the problem with a diamond inheritance?

#### Did you encounter any problem with protected member variables and, if so, how did you solve them?

## Code templates
Code templates are provided to you under _DD1388/labblydelser/2022/lab_04/_. To download them it's recommended to just clone the labblydelser-repo and copy the lab 4 files to your own personal repository at _cprog22/[your KTH-id]\_labbar/04/_. 

It is a _requirement_ that your classes have their own .h/.cpp-pairs, except classes that don't need a .cpp-file for 
method definitions, such as the ChessMove-class below. These code templates will serve as a good guide to solving this lab by
explicitly specifying the relationship between different modules and header-files for you. As you have seen already 
in lab 1, classes can have circular dependencies. One way to solve them is by using forward declarations rather 
than #include preprocessor directives whenever possible. If the full definition of a forward-declared class is needed, 
you can have the required #includes in the .cpp-files. This is precisely what we've done in the code templates for 
this lab.

## Using matrix and smart pointers

You must use your Matrix class from lab 2 to represent the chess
board. You should  use
[shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr) for your chesspieces.

Example:

```c++
Matrix< std::shared_ptr<ChessPiece> > chessboard(8);    // private member of chess board
std::shared_ptr<ChessPiece> a_king = std::make_shared<King>(/* constructor arguments */); // 
```

or

```c++
std::vector< std::shared_ptr<ChessPiece> > white_pieces(16);   // or 32 for all pieces
std::shared_ptr<ChessPiece> a_king = std::make_shared<King>(/* constructor arguments */); // 
```
You can still have raw pointers in the Matrix or ChessMove pointing to the pieces in the vector of shared pointers.

To delete a piece, assign the shared_ptr to null_ptr. You do need to
check for memory leaks in this assignment.

### std
Use the namespace std in this assignement
```
using namespace std;
```

## Chesspiece

```c++
class ChessPiece {
    friend void ChessBoard::move_piece(ChessMove p);
protected:                               // protected will cause problems
    int m_x, m_y;
    bool m_is_white;
    ChessBoard * m_board;
    /**
    * Returns 0 if target square is unreachable.
    * Returns 1 if target square is reachable and empty.
    * Returns 2 if move captures a piece.
    */
    virtual int validMove(int to_x, int to_y);
    virtual char32_t utfRepresentation();     // may be implemented as string
    virtual char latin1Representation();
public:
    // Constructor
    ChessPiece( int x, int y, bool is_white, ChessBoard * board);
    /**
    * Checks if this move is valid for this piece and captures
    * a piece of the opposite color.
    */
    bool capturingMove(int to_x, int to_y);
    /**
    * Checks if this move is valid but does not capture a piece.
    */
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();
    
    /**
    * For testing multiple inheritance
    */
    int unnecessary_int;
};
```

* _capturingMove_ and _nonCapturingMove_ call the protected function _validMove_  .

* _capturingMoves_  returns a _vector_ with _ChessMoves_ that captures a piece of the opposing color

* _nonCapturingMoves_ returns a _vector_ with _ChessMoves_ that moves to an empty space.

You may add private or protected functions to the design of _ChessPiece_ class

The access specifier _protected_ will cause problems that you have to
solve. You can solve them by adding public accessor functions or by
using [friend](https://en.cppreference.com/w/cpp/language/friend) or
by changing the protected access specifier to something else. Describe your 
solution in the corresponding question in the inquiry file.

### Constructors

The derived classes may use the base constructor instead of implementing their own. Use the following syntax (requires c++11)
```c++
   using ChessPiece::ChessPiece;
```

### King

Let Δx be abs(x1-x2) and Δy be abs(y1-y2)

Then either Δx * Δy is one or Δx + Δy is one


### Knight

A possible implementation to check valid moves for knights is to check if Δx² + Δy² is 5.

### Pawn

You may skip en passant move.

An implementation for capturingmove is to check y+1, x+1 and x-1 and for the other color; y-1, x+1 and x-1.

The non-capturing move needs to check if there is a blocking piece at y+1/y-1.

If the pawn is at starting position (second row) it may move 1 or 2 squares ahead

If the pawn is one row from last, the pawn till transform to another piece.

### Bishop and Rook

Implement two classes for Rook and Bishop that implements _ChessPiece_

### Queen

Implement a Queen class that inherits from both _Bishop_ and
_Rook_. This will create a diamond inheritance which is generally
considered dangerous and one of the reasons many programming languages
do not allow multiple inheritance.

#### Create a queen object and try to set the unnecessaryInt in _ChessPiece_. What happens?  

#### Think about if it would be better if the queen had a bishop and a rook (as members) instead of inherited from them?


## Board encoding

Your test program will accept text input in the form of chessboard
states. The states will be encoded according to these rules.
```
R = Rook ("Torn" in Swedish) 
N = kNight [sic] ("Springare" or "Häst" in Swedish) 
B = Bishop ("Löpare" in Swedish) 
Q = Queen 
K = King 
P = Pawn
. = Empty square 
```

White pieces are denoted with uppercase letters and black pieces are denoted with lowercase letters.
Every line has 8 symbols and ends with a newline.  Every board consists of 8 lines.


Each class that inherits from ChessPiece should implement an utf8-representation that uses the [utf8-representation](https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode) of chess pieces AND a latin1-representation according to the table above (R,n,Q... etc.)

* _utfRepresentation_

* _latin1Representation_


## Chess move

A chess move is defined as

```c++
struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece;   // you can change the position of the chess piece with this pointer.
};
```

## Chess board

Implement a chess board class that contains your chess pieces. You
must use your Matris class from lab2 to represent the chess
board. You may add additional functions or members (public
constructors or vectors with white and black pieces) to the
_ChessBoard_ class.


```c++
using std::vector;
using std::istream;
using std::string;

class ChessBoard {
    // add additional members or functions of your choice

private:
    Matrix<ChessPiece *> m_state; // Matrix from lab 2
    vector<shared_ptr<ChessPiece>> m_white_pieces;
    vector<shared_ptr<ChessPiece>> m_black_pieces;
    
public:
    void move_piece(ChessMove chess_move);
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);

};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);
```



## Sample program

```c++
using std::vector; using std::stringstream; using std::cout; using std::endl;
//...
    ChessBoard chess;
    stringstream s;
    s << ".....Q.." << endl;
    s << "...q...." << endl;
    s << "......Q." << endl;
    s << "q......." << endl;
    s << ".......Q" << endl;
    s << ".q......" << endl;
    s << "....Q..." << endl;
    s << "..q.....";
    s >> chess;
    vector<ChessMove> v = chess.capturingMoves(true);

    if (v.size() != 0) {
        cout << "capturingMoves FAILED, expected 0 moves but got " << v.size() << " moves" << endl;
    } else {
        cout << "capturingMoves PASSED, expected 0 moves and got " << v.size() << " moves" << endl;
    }
```

## Tests

For this assignment, do _not_ write unit tests for each function.

There are some simple testboards in _lab\_04/tests.in_ that only tests the number of valid capturing moves.

Expand the tests with more boards and verify that the sizes of the vectors from capturingMoves and nonCapturingMoves are as expected.

By only testing capturingMoves and nonCapturingMoves, you are implicitly testing the underlying functions. However, beware that if one chess piece is incorrectly reported as have 1 extra capturing move, while another is reported as having one less, then the test of capturingMoves will pass, which it ideally shouldn't.

Make sure that your test program verifies capturingMoves and nonCapturingMoves automatically by comparing the results with the expected results. The user that runs the test program should either get a success message or get a failure message that indicates which board has failed. The program _lab\_04/tests.cpp_ should help with this.

# Losing chess AI (slagschack)

Implement two AI that plays the game [losing chess](https://en.wikipedia.org/wiki/Losing_chess), a variation of chess where the object is to lose all your pieces to an opponent who is forced to capture whenever possible.
For the purposes of this lab, you can skip castling ("Rockad" in Swedish), En Passant and moves that place the king in check but you do need to implement [pawn promotion](https://en.wikipedia.org/wiki/Promotion_%28chess%29)

Use the given struct/classes from the previous assignment but add
member values/functions when needed.


## AI 1 - random thinker

* If there are no capturing moves, this AI will perform a non capturing at random.

* If there are several capturing moves, the AI will perform one of them at random.

* If there is a pawn promotion, a random piece will be selected.

## AI 2 - thinks one step ahead. but defaults to random

* If there are no capturing moves
    - Check if any non-capturing move will force a capturing move for the opponent.
    - If not, play a random move.

* If there are several capturing moves
    - Check if any capturing move will force a capturing move for the opponent
    - If not, play a random capturing move.

* If there is a pawn promotion
    - If possible, pick a piece that can not capture on its next move.
    - If not possible, promote to a random piece.


## Play the game

Let the two AI play against each other and print the gameboard after each move.
As before the game should be initialized by reading a starting board (not
necessarily the chess standard starting positions).

Let the starting color and kind of AI be command line options to your program.

