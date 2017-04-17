#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
    bool placed;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;
// typedef AVLTree<int, Rectangle> InputMapType;
// typedef AVLTree<int, std::pair<int, int> > OutputMapType;


// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
  os << r.ID;
  return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
  os << p.first << "," << p.second;
  return os;
}



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}



// Write your backtracking search function here
bool isValid(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    //reached the edge
    if ((n < x1 + r.length) || (m < y1 + r.height)) {
        return false;
    }

    //parse through grid, check if new location inhabited
    for (int i = x1; i < x1 + r.length; i++) {
        for (int j = y1; j < y1 + r.height; j++) {
            //not occupied
            if(grid[i][j] == false){
                continue;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool backtrackingSearch(OutputMapType& outputMap, vector<vector<bool> >& grid, 
                        InputMapType::iterator input_it, InputMapType& inputMap)
{
    //if we've reached the very end of the board
    if (input_it == inputMap.end()) {
        return true;
    }

    for (unsigned int i = 0; i < grid.size(); i++) {
        for (unsigned int j = 0; j < grid[i].size(); j++) {
            InputMapType::iterator temp = input_it;
            if(isValid(i, j, input_it->second, grid)) {
                flip(i, j, input_it->second, grid);
                if (backtrackingSearch(outputMap, grid, ++temp, inputMap)) {
                    //outputMap.insert(std::pair<int, int> (i, j));
                    outputMap.insert(make_pair(input_it->first, pair<int, int>(i, j)));
                    return true;
                } else {
                    outputMap.erase(input_it->first);
                }
            } else {
                //rotate the rectangle
                int length = (input_it->second).length;
                (input_it->second).length = (input_it->second).height;
                (input_it->second).height = length;

                if(isValid(i, j, input_it->second, grid)) {
                    flip(i, j, input_it->second, grid);
                    outputMap.insert(make_pair(input_it->first, pair<int, int>(i, j)));
                    if (backtrackingSearch(outputMap, grid, ++temp, inputMap)) {
                    outputMap.insert(make_pair(input_it->first, pair<int, int>(i, j)));
                    return true;
                    } else {
                        outputMap.erase(input_it->first);
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    //checking if bad filename
    if (ifile.fail()) {
        cout << "Couldn't open file" << endl;
        return 1;
    }
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
	    r.placed = false;

        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;
    
    for (int i = 0; i < n; i++)
    {
      grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here
    solution_exists = backtrackingSearch(output, grid, it, input);

    if (!solution_exists) {
      ofile << "No solution found.";
    }
    else {
      printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}
