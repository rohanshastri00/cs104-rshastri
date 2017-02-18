#ifndef LLISTINT_H
#define LLISTINT_H
#include <ostream>

using namespace std;

class LListInt {
 public:
  struct Item {
    Item(int v, Item* p, Item* n) { val = v; prev = p; next = n; }
    int val;
    Item *prev;
    Item *next;
  };


  /**
   * Default constructor - empty list
   */
  LListInt();

  /**
   * Destructor
   */
  ~LListInt();


  /**
   * Copy constructor [must run in O(n) where n=size of other]
   *   Be careful you don't give us an O(n^2) implementation
   */
  LListInt(const LListInt& other);

  /**
   * Assignment Operator (must run in O(n + m) where
   *   n is the size of this list & m is the size of other
   *   Be careful you don't give us an O(n^2) or O(m^2) implementation
   */
  LListInt& operator=(const LListInt& other);

  /**
   * Adds an item to the back of the list in O(1) time
   */
  void push_back(const int& val);


  /**
   * operator+=
   *
   * Write an appropriate operator overload function to support the following:
   *    LListInt mylist1, mylist2;  mylist1 += mylist2;
   * This operation should remove all elements from mylist2 in FIFO order and 
   * add them the back of mylist1 without allocating or freeing memory 
   *  (i.e. take the elements from mylist2 and just link them in to mylist 1)
   *
   * This function must run in O(1) and mylist2 should be empty upon completion.
   *
   * Note 1:  mylist1 += mylist2 += mylist3 should also work and produce the
   *          in mylist1 the concatenation of all 3 lists, leaving mylist2 and 
   *          mylist3 empty.  
   *
   * Note 2: myList1 += myList1 should be prohibited. 
   */

  LListInt& operator+=(LListInt& other);

    /**
   * Ostream operator << should Output the contents of the list 10 per line
   *  (separated by spaces) to the given ostream object
   *
   *  cout << mylist << "...that's all the numbers!" << endl;
   *
   * Must run in O(n) and NOT O(n^2)
   */

  //ostream& operator<<(ostream& output);

  friend ostream& operator<<(ostream& output, const LListInt& list);


  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos
   */
  void insert(int pos, const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove(int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set(int pos, const int& val);

  /**
   * Returns the value at index, pos
   */
  int& get(int pos);

  /**
   * Returns the value at index, pos
   */
  int const & get(int pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();

 private:
  /** 
   * Returns a pointer to the item at index, pos
   *  and NULL otherwise
   */
  Item* getNodeAt(int pos) const;

  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif
