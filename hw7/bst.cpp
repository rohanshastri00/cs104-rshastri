#include "bst.h"
#include <iostream>

using namespace std;

int main()
{
	BinarySearchTree<int, int> test;
	test.insert(make_pair(2,2));
	test.insert(make_pair(3,3));
	test.insert(make_pair(7,7));
	test.insert(make_pair(4,4));
	test.insert(make_pair(6,6));
	test.insert(make_pair(5,5));

	test.print();

	cout << endl;

	BinarySearchTree<int, int>::iterator it = test.begin();

	cout << it->second << endl;

	BinarySearchTree<int, int>::iterator find_test = test.find(4);

	cout << find_test->second << endl;

	find_test = test.find(8);

	if (find_test == test.end()){
		cout << "could not find 8" << endl;
	}

	BinarySearchTree<int, int>::iterator final_it;

	for (final_it = test.begin(); final_it != test.end(); ++final_it){
		cout << final_it->second << " ";
	}

	cout << endl;

	return 0;
}