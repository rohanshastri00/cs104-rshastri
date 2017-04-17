#include <iostream>
#include "avlbst.h"
//#include "bst.h"
using namespace std;

int main() {

	AVLTree<int, int> myTree;

	myTree.insert(make_pair(3, 3));
	myTree.insert(make_pair(4, 4));
	myTree.insert(make_pair(2, 2));
	myTree.insert(make_pair(5, 5));
	myTree.insert(make_pair(6, 6));
	myTree.insert(make_pair(1, 1));
	myTree.insert(make_pair(10, 10));
	myTree.insert(make_pair(12, 12));
	myTree.insert(make_pair(7, 7));
	myTree.insert(make_pair(8, 8));


	// Remove Example
	myTree.erase(12);
	myTree.AVLTreePrint();
	std::cout << std::endl;

	myTree.erase(3);
	myTree.AVLTreePrint();
	std::cout << std::endl;

	myTree.erase(8);
	myTree.AVLTreePrint();
	std::cout << std::endl;

}