#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};
// returns head pointer to new list
Item* concatenate(Item* head1, Item* head2)
{

	if (head2 == NULL)
	{
		return NULL;
	}
	//head1 will equal null after the last
	//iteration of the first list
	if (head1 == NULL)
	{ 
		Item* copy = new Item(head2->val, NULL);
		copy->next = concatenate(head1, head2->next);
		return copy;
	}

	if (head1 != NULL)
	{
		Item* copy = new Item(head1->val, NULL);
		//if you reach the end of the first list
		if (head1->next == NULL)
		{
			copy->next = head2;
		}
		copy->next = concatenate(head1->next, head2);
		return copy;
	}

	return NULL;
}


void removeEvens(Item*& head)
{	
	//reached end of the list
	if(head->next == NULL)
	{
		return;
	}

	//if first element is even
	if (head->val % 2 == 0)
	{
		Item* temp = head;
		delete temp;
		head = head->next;

	}

	//if the next value is even
	if (head->next->val % 2 == 0)
	{
		Item* temp = head->next;
		head->next = head->next->next;
		delete temp;
		//call for temp	
		removeEvens(head->next);
	}

	if (head->val % 2 == 1)
	{
		removeEvens(head->next);
	}

}

double findAverageHelper (Item* head, double& counter)
{
	if (head == NULL)
	{
		return 0.0;
	}
	else 
	{	
		counter++;
		return head->val + findAverageHelper(head->next, counter);
	}

}

// return 0.0 if the list is empty
double findAverage(Item* head)
{
	double counter = 0.0;
	//when you reach the end of the list;
	if (head == NULL)
	{
		return 0;
	}	
	else 
	{
		return (findAverageHelper(head, counter))/counter;

	}

	if (head == NULL)
	{
		return 0.0;
	}

}




void printList(ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);   
  }
}


int main (int argc, char* argv[])
{

	if(argc < 2){
    cerr << "Please provide a file name for output" << endl;
    return 1;
  	}

 	ifstream ifile(argv[1]);
  	if(ifile.fail()){
    cerr << "Unable to open input file" << endl;
    return 1;
  	}

  	Item* head1 = NULL;
  	Item* head2 = NULL;

  	//read ints, make linked lists
  	string buffer;
  	int inputNum;
  	//start with reeading in for list 1
  	int whatList = 1;
  	while (getline(ifile, buffer))
  	{
    stringstream stream(buffer);
		while (stream >> inputNum)
	 	{
			//puts each individual num into the linkedlist
			Item* current  = new Item(inputNum, NULL);
			if (whatList == 1)
			{
				//if it's the first element, define it as the head
				if (head1 == NULL)
				{
					head1 = current;
				}
				else 
				{
					Item* temp = head1;
					while(temp->next)
					{
						temp = temp->next;
					}
					temp->next = current;

				}
			}

			if (whatList == 2)
			{
				if (head2 == NULL)
				{
					head2 = current;
				}

				else 
				{
					Item* temp = head2;
					while(temp->next)
					{
						temp = temp->next;
					}
					temp->next = current;

				}
			}
			
		}
		whatList++;
	}	

	ofstream output(argv[2]);
	Item* head3 = concatenate(head1, head2);
	printList(output, head3);

	removeEvens(head3);
	printList(output, head3);

	cout << findAverage(head3) << endl;
	printList(output, head3);

	//write average to the output file
	output << findAverage(head3);

	while (head1 != NULL){
		delete head1;
		head1 = head1->next;
	}

	while (head2 != NULL){
		delete head2;
		head2 = head2->next;
	}

	while (head3 != NULL){
		delete head3;
		head3 = head3->next;
	}
}