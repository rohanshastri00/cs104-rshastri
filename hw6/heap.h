#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>


template <typename T, typename Comparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  void print();



 private:
  /// Add whatever helper functions and data members you need below
  void heapify(int idx);
  std::vector<T> items_;
  Comparator comp;
  int type;
  void trickleUp(int loc);

};

// Add implementation of member functions here

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  return items_[0];
}



// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  items_[0] = items_.back();
  items_.pop_back();
  heapify(0);
}




template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c) 
  : comp(c), type(m)
{

}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{

}


template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{
  items_.push_back(item);
  trickleUp(items_.size()-1);
}



template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc)
{ 
  //while parent index is valid 
  if (loc == 0) {
    return;
  }
  int parent = (loc-1) / type;
  if (comp(items_[loc], items_[parent])) {
    std::swap(items_[parent], items_[loc]);
    trickleUp(parent);
  }
}



template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
  if (items_.size() == 0)
  {
    return true;
  }
  return false;
}



template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int idx)
{ 
  if((type*idx)+1 >= items_.size()) return;
  int smallerChild= (type*idx)+1; // start w/ left
  int currChild;
  //iterate through all children
  for (int i = 1; i < type; i++) {
    if (((type*idx)+i) < items_.size()) {
      currChild = smallerChild+i;
    //if the currChild is less than the smallest,
    //make it the smallest
    if(comp(items_[currChild], items_[smallerChild]))
      smallerChild = currChild;
    }
  }

  if(!(comp(items_[idx], items_[smallerChild]))) {
    std::swap(items_[idx], items_[smallerChild]);
    heapify(smallerChild);
  } 
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::print()
{
  for (int i = 0; i < items_.size();i++) {
    std::cout << items_[i] << " ";
  }
  std::cout << std::endl;
}



#endif

