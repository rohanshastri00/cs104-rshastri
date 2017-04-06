#include "puzzle_move.h"

using namespace std;

  PuzzleMove::PuzzleMove(Board* board)
    : tileMove(-1), b(board), g(0), prev(NULL) { }

   PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
    : tileMove(tile), b(board), g(parent->g + 1), prev(parent)
  { }

  // Destructor
   PuzzleMove::~PuzzleMove() { delete b; }
