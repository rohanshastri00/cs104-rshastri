#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "puzzle_solver.h"


  // Constructor (makes a copy of the Board and stores it in b_)
  //  Also takes a PuzzleHeuristic which will score boards
  PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph)
  	: b_(b), expansions_(0), ph_(ph)
  {
  }

  // Destructor
  PuzzleSolver::~PuzzleSolver()
  {

  }

  // Run the A* search and builds the solution and tracks
  // the number of expansions
  void PuzzleSolver::run()
  {
  	//PuzzleMoveScoreComp scoreComp;
  	Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2);
  	PuzzleMoveSet closed_list;

  	Board* initCopy = new Board(b_);
  	PuzzleMove* newPuzzle = new PuzzleMove(initCopy);
  	open_list.push(newPuzzle);
  	closed_list.insert(newPuzzle);
	int currtile;
  	while (!(open_list.empty())){
  		PuzzleMove* current_move = open_list.top();
  		open_list.pop();
  		if (current_move->b->solved()){
  			while (current_move->prev != NULL){
  				currtile = current_move->tileMove;
  				solution_.push_back(currtile);
  				current_move = current_move->prev;
  			}
  			break;
  		}

  		map<int, Board*> potential_moves = current_move->b->potentialMoves();
  		map<int, Board*>::iterator pMoves_it;
  		//iterate through the potential moves map
  		for (pMoves_it = potential_moves.begin(); pMoves_it != potential_moves.end(); ++pMoves_it){
  			//calc hueristic for each board*
  			PuzzleMove* temp = new PuzzleMove(pMoves_it->first, 
  												pMoves_it->second, 
  												current_move);
			//when a tile has not been explored
  			if(closed_list.find(temp) == closed_list.end()){
  				temp->h = ph_->compute(*(pMoves_it->second));
  				open_list.push(temp);
  				expansions_++;
  				closed_list.insert(temp);
  			}
  			else {
  				delete temp;
  			}
  		}
  	}
  	PuzzleMoveSet::iterator cl_it;
  	for(cl_it = closed_list.begin(); cl_it != closed_list.end();++cl_it){
  		delete *cl_it;
  	}
  }

  // Return the solution deque
  std::deque<int> PuzzleSolver::getSolution()
  {
  	return solution_;
  }

  // Return how many expansions were performed in the search
  int PuzzleSolver::getNumExpansions()
  {
  	return expansions_;
  }