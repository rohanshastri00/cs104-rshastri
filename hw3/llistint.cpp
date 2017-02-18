#include "llistint.h"
#include <cstdlib>
#include <iostream>
#include <ostream>
using namespace std;


LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}


LListInt::LListInt(const LListInt& other)
{
  //initialize this new list
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  //if other is empty
  if (other.head_ == NULL)
  {
    return;
  }
  //now copying all elements from previous int list
  Item* temp = other.head_;
  while (temp != NULL)
  {
    this->insert(this->size(), temp->val);
    temp = temp->next;
    //dont need to increment size, insert does it for me
  }
  this->size_ = other.size_;
}

LListInt& LListInt::operator=(const LListInt& other)
{
  //check if lists are equal 
  if (this == &other)
  {
    return *this;
  }

  //the LHS should not have anything in it to begin with
  this->clear();
  //init this new list
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;

  if (other.head_ == NULL)
  {
    return *this;
  }

  Item* temp = other.head_;

  while (temp != NULL)
  {
    this->insert(size_, temp->val);
    temp = temp->next;
    //dont need to increment size, insert does it for me
  }

  this->size_ = other.size_;
  return *this;
  
}


void LListInt::push_back(const int& val)
{
  this->insert(this->size(), val);
}


LListInt& LListInt::operator+=(LListInt& other) 
{


  //if this is empty and other is not
  if (this->empty() && !(other.empty()))
  {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->size_ = other.size();
    other.head_ = NULL;
    other.tail_ = NULL;
    other.size_ = 0;
    return *this;
  }
  //if this is the same as other
  if (this->head_ == other.head_)
  {
    other.head_ = NULL;
    other.tail_ = NULL;
    other.size_ = 0;
    return *this;
  }
  //if other is empty
  if (other.empty() && !(this->empty()))
  {
    return *this;
  }
  //else 

  this->tail_->next = other.head_;
  other.head_->prev = this->tail_;

  this->tail_ = other.tail_;

  this->size_ += other.size();; 

  other.head_ = NULL;
  other.tail_ = NULL;

  other.size_ = 0;

  return *this;
}


ostream& operator<<(ostream& output, const LListInt& list) {

  LListInt::Item* temp = list.getNodeAt(0);
  int linecount = 0;
  while (temp != NULL)
  {
    if (linecount == 10)
    {
      output << endl;
      linecount = 0;
    }
    output << temp->val << " ";
    linecount++;
    temp = temp->next;
  }   
  return output;
}

/**
* Inserts val so it appears at index, pos
*/
void LListInt::insert(int loc, const int& val)
{
    //check bounds for the function
  if (loc < 0 || loc > size_)
  {
    return;
  }
  //if list is empty
  if (head_== NULL && loc == 0)
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
    Item* newNode = new Item(val, NULL, NULL);
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
    size_++;
    return;
  }
  //if placing at end of the list
  if (loc == size_)
  {
    Item* temp = tail_;
    Item* newNode = new Item(val, NULL, NULL);
    newNode->prev = temp;
    temp->next = newNode;
    tail_ = newNode;
    size_++;
    return;
  }
  //any other location (in the middle)
  if (loc > 0 && loc <= size_-1)
  {

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
    return;
  }
  else {
    return;
  }
  
}

 /**
   * Removes the value at index, pos
   */
void LListInt::remove(int loc)
{

  //checking if valid loc
  if (loc < 0 || loc >= size_)
  {
    return;
  }

  //if there is no original node
  if (head_ == NULL)
  {
    return;
  }

  //if removing the only element
  if (size_ == 1)
  {
    Item* temp = getNodeAt(loc);
    size_--;
    head_ = NULL;
    tail_ = NULL;
    delete temp;
    return;
  }

  //removing from front
  if (loc == 0)
  {
      Item* temp = head_;
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
      Item* temp = tail_;
      Item* left = getNodeAt(loc-1);
      tail_ = left;
      left->next = NULL;
      delete temp;
      size_--;
      return;
  }

    //all other positions
  if (loc > 0 && loc < size_-1)
  { 
      Item* temp = getNodeAt(loc);
      Item* right = getNodeAt(loc+1);
      Item* left = getNodeAt(loc-1);
      left->next = right;
      right->prev = left;
      delete temp;
      size_--;
      return;
  }
  else 
  {
      return;
  }

}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
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
