#include "heap.h"
#include <functional>

int main()
{
	//binary tree, greater than
	std::greater<int>greatComp;
	Heap<int, std::greater<int> > bintest(2, greatComp);
	bintest.push(7);
	bintest.push(18);
	bintest.push(9);
	bintest.push(19);
	bintest.push(35);
	bintest.push(14);
	bintest.push(10);
	bintest.push(28);
	bintest.push(39);
	bintest.push(36);
	bintest.push(43);
	bintest.push(16);
	bintest.push(25);
	//check if push, trickleUp + print functions work
	std::cout << "BIN TEST" << std::endl;
	bintest.print();
	//checking if push, trickleUp work w out of place element
	bintest.push(56);
	bintest.print();
	//checking if pop, heapify work w bin tree
	bintest.pop();
	bintest.pop();
	bintest.pop();
	bintest.pop();
	bintest.print();



	//tri-nary tree, less than
	Heap<int> tritest(3);
	tritest.push(7);
	tritest.push(18);
	tritest.push(9);
	tritest.push(19);
	tritest.push(35);
	tritest.push(14);
	tritest.push(10);
	tritest.push(28);
	tritest.push(39);
	tritest.push(36);
	tritest.push(43);
	tritest.push(16);
	tritest.push(25);
	std::cout << "TRI TEST" << std::endl;
	tritest.print();
	tritest.push(3);
	tritest.print();
	//checking if pop, heapify work w bin tree
	tritest.pop();
	tritest.pop();
	tritest.pop();
	tritest.pop();
	tritest.pop();
	tritest.pop();
	tritest.print();

	//check if top works
	std::cout << test.top() << std::endl;

	return 0;
}