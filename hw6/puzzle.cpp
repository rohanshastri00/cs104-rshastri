#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  Board* b = new Board(n, initMoves, seed);
  cout << *b << endl;
  PuzzleSolver* solutionPuzzle;
  PuzzleHeuristic* ph;
  if (heur == 0){
    ph = new PuzzleBFSHeuristic;
  }
  else if (heur == 1){
    ph = new PuzzleOutOfPlaceHeuristic;
  }
  else if (heur == 2){
  	ph = new PuzzleManhattanHeuristic;
  }

  while (!(b->solved())){
  	cout << "Enter tile number to move or -1 for a cheat: ";

  	int userChoice;
  	cin >> userChoice;

  	if (userChoice > 0 && userChoice < n*n){
  		b->move(userChoice);
  		cout << *b << endl;
  	}
  	if (userChoice == 0){
  		cout << "Goodbye!" << endl;
  		break;
  	}
  	if (userChoice == -1){
  		cout << "Try this sequence: " << endl;
  		solutionPuzzle = new PuzzleSolver(*b, ph);
  		solutionPuzzle->run();
  		deque<int> tileSolution = solutionPuzzle->getSolution();
  		for (int i = tileSolution.size()-1; i != -1; --i) {
  			cout << tileSolution[i] << " ";
  		}
  		cout << endl;
  		int expansions = solutionPuzzle->getNumExpansions();
  		cout << "(Expansions = " << expansions << ")" << endl;
  		cout << endl << endl;
  		cout << *b << endl;
  		delete solutionPuzzle;
  	}

  }
 delete ph;
 delete b;

  return 0;
}
