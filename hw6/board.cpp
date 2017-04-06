#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& obj) {
  //allocate the space
  tiles_ = new int[obj.size()];
  size_ = obj.size();

  for (int i = 0; i < obj.size(); i++) {
    //copy contents of tiles
    this->tiles_[i] = obj[i];
  }
}

Board::~Board()
{
  delete[] tiles_;
}

Board& Board::operator=(const Board& obj){
  if (this == &obj){
    return *this;
  }
  delete[] tiles_;
  tiles_ = new int[obj.size()];
  size_ = obj.size();

  for (int i = 0; i < obj.size(); i++) {
    //copy contents of tiles
    this->tiles_[i] = obj[i];
  }
  return *this;
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{

  map<int, Board*> moveMap;
  //clear moveMap
  int side_dim = dim();
  int br, bc;
  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);
  br = j / side_dim;
  bc = j % side_dim;
  //if rows + cols are in bounds
  //ntr = NEW TILE ROW
  //ntc = NEW TILE COL
  int ntr;
  int ntc;
  //moving up 
  if (br - 1 >= 0) {
    if (j-side_dim >= 0) {
      Board* b = new Board(*this);
      ntr  = j-side_dim;
      b->move(tiles_[ntr]);
      moveMap.insert(make_pair(tiles_[ntr], b));
    }
  }
  //moving down 
  if (br + 1 < side_dim) {
    if (j+side_dim < size_) {
      Board* b = new Board(*this);
      ntr  = j+side_dim;
      b->move(tiles_[ntr]);
      moveMap.insert(make_pair(tiles_[ntr], b));
    }
  }
  //moving left
  if (bc - 1 >= 0) {
    if (j-1 >= 0) {
      Board* b = new Board(*this);
      ntc  = j-1;
      b->move(tiles_[ntc]);
      moveMap.insert(make_pair(tiles_[ntc], b));
    }
  }
  //moving right
  if (bc + 1 < side_dim) {
    if (j+1 < size_) {
      Board* b = new Board(*this);
      ntc  = j+1;
      b->move(tiles_[ntc]);
      moveMap.insert(make_pair(tiles_[ntc], b));
    }
  }
  //find whatever tiles are moveable (up to 4)
  //call move on those boards
    //create copies of "this" board using constructor, call move on those
  //insert into map, int key is the tile no.
  return moveMap;
}

bool Board::solved() const
{
  for (int i = 0; i < size_;i++) {
    if(this->tiles_[i] !=  i) {
      return false;
    }
  }
  return true;
}

bool Board::operator<(const Board& rhs) const
{
  for (int i = 0; i < size_; i++) {
    if(this->tiles_[i] < rhs[i]) {
      return true;
    }
    if(this->tiles_[i] > rhs[i]) {
      return false;
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int side_dim = b.dim();
  int index = 0;
  for (int i = 0; i < side_dim; i++) {
    b.printRowBanner(os);
    for(int j = 0; j < side_dim; j++) {
      os << "|";
      if (index < b.size() && b[index] != 0 && b[index] < 10) {
        os << " " << b[index];
      } 
      else if(b[index] >= 10) {
        os << b[index];
      }
      else {
        os << "  ";
      }
      ++index;
    }
    os << "|" << '\n';
  }
  b.printRowBanner(os);

  return os;
}



const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
