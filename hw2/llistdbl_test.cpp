#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {

  LListDbl list;

    //should look like: 4 5 6 7 8 9 10 11 12
    //front
    list.insert(0, 6);
    list.insert(0, 5);
    list.insert(0, 4);

  if (list.get(0) == 4) {
    cout << "SUCCESS: 4 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 4 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  }

  if (list.get(1) == 5) {
    cout << "SUCCESS: 5 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 5 is not at the 1st index of the list, " << list.get(1);
    cout << " is instead." << endl;
  }



    //back
    list.insert(list.size()-1, 10);
    list.insert(list.size()-1, 11);
    list.insert(list.size()-1, 12);

    if (list.get(list.size()-1) == 12) {
    cout << "SUCCESS: 12 is at the last index of the list." << endl;
  } else {
    cout << "FAIL: 12 is not at the last index of the list, " << list.get(list.size()-1);
    cout << " is instead." << endl;
  }

	if (list.get(list.size()-2) == 11) {
    cout << "SUCCESS: 11 is at the second to last index of the list." << endl;
  } else {
    cout << "FAIL: 11 is not at the second to last index of the list, " << list.get(list.size()-2);
    cout << " is instead." << endl;
  }



    //middle
    list.insert(3,7);
    list.insert(4,8);
    list.insert(5,9);

    if (list.get(4) == 8) {
    cout << "SUCCESS: 8 is at the 4th index of the list." << endl;
  } else {
    cout << "FAIL: 8 is not at the 4th index of the list, " << list.get(4);
    cout << " is instead." << endl;
  }

     if (list.get(5) == 9) {
    cout << "SUCCESS: 9 is at the 5th index of the list." << endl;
  } else {
    cout << "FAIL: 9 is not at the 5th index of the list, " << list.get(5);
    cout << " is instead." << endl;
  }

  //current list: 4 5 6 7 8 9 10 11 12
  	//remove front

   list.remove(0);
    if (list.get(0) == 5) {
    cout << "SUCCESS: 5 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 5 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  }

  list.remove(0);
   if (list.get(0) == 6){ 
    cout << "SUCCESS: 6 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 6 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  }

  //current list: 6 7 8 9 10 11 12

  //remove back
list.remove(list.size()-1);
  if (list.get(list.size()-1) == 11) {
    cout << "SUCCESS: 11 is at the last index of the list." << endl;
  } else {
    cout << "FAIL: 11 is not at the last index of the list, " << list.get(list.size()-1);
    cout << " is instead." << endl;
  }

list.remove(list.size()-1);
  if (list.get(list.size()-1) == 10) {
    cout << "SUCCESS: 10 is at the last index of the list." << endl;
  } else {
    cout << "FAIL: 10 is not at the last index of the list, " << list.get(list.size()-1);
    cout << " is instead." << endl;
  }

  //current list: 6 7 8 9 10


  //remove middle
  list.remove(2);
   if (list.get(2) == 9) {
    cout << "SUCCESS: 9 is at the 2nd index of the list." << endl;
  } else {
    cout << "FAIL: 9 is not at the 2nd index of the list, " << list.get(2);
    cout << " is instead." << endl;
  }
  list.remove(1);
   if (list.get(1) == 9) {
    cout << "SUCCESS: 9 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 9 is not at the 1st index of the list, " << list.get(1);
    cout << " is instead." << endl;
  }

  cout << "PASSED ALL TESTS!" << endl;

  return 0;


 }