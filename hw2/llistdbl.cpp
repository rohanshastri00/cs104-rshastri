#include "llistdbl.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
* Inserts val so it appears at index, pos
*/
void LListDbl::insert(int loc, const double& val)
{
    //check bounds for the function
  if (loc < 0 || loc > size_)
  {
    return;
  }
  //if list is empty
  if (head_ == NULL)
  {
    //new node about to be placed
    Item* newNode = new Item(val, NULL, NULL);
    head_ = newNode;
    tail_ = newNode;
    size_++;
    return;
  }

  //if placing at the start of the list
  if (loc == 0)
  {

    //original node
    Item* temp = getNodeAt(loc);
    Item* newNode = new Item(val, NULL, NULL);
    newNode->next = temp;
    temp->prev = newNode;
    head_ = newNode;
    size_++;
    return;
  }
  //if placing at end of the list
  if (loc == size_-1)
  {
    Item* temp = getNodeAt(loc);
    Item* newNode = new Item(val, NULL, NULL);
    newNode->prev = temp;
    temp->next = newNode;
    tail_ = newNode;
    size_++;
    return;
  }

    //any other location:
    Item* temp = getNodeAt(loc);
    Item* newNode = new Item(val, NULL, NULL);
    //the og node gets shifted right
    newNode->next = temp;
    //og node now has new node behind it
    temp->prev = newNode;
    //the node behind the new node
    Item* behind = getNodeAt(loc-1);
    newNode->prev = behind;
    //also update that node
    behind->next = newNode;
    size_++;
  
}

 /**
   * Removes the value at index, pos
   */
void LListDbl::remove(int loc)
{

  //checking if valid loc
  if (loc < 0 || loc > size_){
    cout << "Invalid location, please re-enter." << endl;
    return;
  }

  //if there is no original node
  if (size_ == 0)
  {
    return;
  }

  //if removing the last element
  if (size_ == 1)
  {
    Item* temp = getNodeAt(loc);
    delete temp;
    size_--;
    head_ = NULL;
    tail_ = NULL;
    return;
  }

  //removing from front
  if (loc == 0)
  {
      Item* temp = getNodeAt(loc);
      Item* right = getNodeAt(loc+1);
      head_ = right;
      right->prev = NULL;
      delete temp;
      size_--;
      return;
  }

  //removing from back
  if (loc == size_-1)
  {
      Item* temp = getNodeAt(loc);
      Item* left = getNodeAt(loc-1);
      tail_ = left;
      left->next = NULL;
      delete temp;
      size_--;
      return;
  }

    //all other positions
    Item* temp = getNodeAt(loc);
    Item* right = getNodeAt(loc+1);
    Item* left = getNodeAt(loc-1);
    left->next = right;
    right->prev = left;
    delete temp;
    size_--;

}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
