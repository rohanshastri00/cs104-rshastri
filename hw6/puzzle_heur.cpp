#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "puzzle_heur.h"
using namespace std;


int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int side_dim = b.dim();
  	int cr, cc, dr, dc;

  	int total = 0;
  	//cmd = current manhattan distance for one tile
  	int cmd;
  	for (int i = 0; i < b.size(); ++i) {
  		if (b[i] != 0) {
  			cr = b[i] / side_dim; 
 			cc = b[i] % side_dim;

 			dr = i / side_dim;
 			dc = i % side_dim;

 			cmd = abs(cr - dr) + abs(cc - dc);
 			total += cmd;
  		}

  	}
  	return total;
}


int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int count  = 0;
	for (int i = 0; i < b.size(); ++i) {
		if (b[i] != i && b[i] != 0) {
			count++;
		}
	}
	return count;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}

