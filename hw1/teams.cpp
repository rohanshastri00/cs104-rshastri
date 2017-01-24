#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}


void generateCombinations (string* namePool, string* team1, 
  string* team2, int team1size, int team2size, int namePoolIndex, int teamSize)
{

  //if both teams are full, print solution

  if (team1size ==  teamSize && team2size == teamSize)
  {
    printSolution (team1, team2, teamSize);
  }


  //if team1 isnt full
  else {
    if (team1size < teamSize)
    {

      //add player 1, recurse everyone else
      team1[team1size] = namePool[namePoolIndex];
      generateCombinations(namePool, team1, team2, 
        team1size+1, team2size, namePoolIndex+1, teamSize);

    }
    //if team2 isnt full
    if (team2size < teamSize)
    {
      //add player 2, recurse everyone else
      team2[team2size] = namePool[namePoolIndex];
      generateCombinations(namePool, team1, team2, 
        team1size, team2size+1, namePoolIndex+1, teamSize);
    }
  }

}


int main(int argc, char* argv[])
{


  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }

  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  int numNames;
  ifile >> numNames;

  //use dynamically allocated string array to store names
  string* names = new string[numNames];

  //now get names into array
  for (int i = 0; i < numNames; i++){
    ifile >> names[i];
  }

  //create two team arrays
  int teamSize = numNames/2;

  string* team1 = new string[teamSize];
  string* team2 = new string[teamSize];
  //now call recursive function
  //put 
  generateCombinations(names, team1, team2, 0, 0, 0, teamSize);


  return 0;
}
