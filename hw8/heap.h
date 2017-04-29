#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void trickleUp(int loc);
    void heapify(int idx);



    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    store_.push_back(make_pair(priority, item));
    keyToLocation_.insert(make_pair(item, store_.size() - 1));
    if (store_.size() - 1 > 1) { trickleUp(store_.size() - 1); }
}


//updates value in heap to new value priority
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    if (keyToLocation_.find(item) == keyToLocation_.end()) {
        return;
    } 
    else {
        int i = keyToLocation_.find(item)->second;
        store_[i].first = priority;
        trickleUp(i);
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    return store_[0].second;

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    
    store_[0] = store_.back();
    store_.pop_back();
    heapify(0);

}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::trickleUp(int loc)
{
    if (loc == 0) { return; }

    int parent = (loc-1) / m_;
    if (c_(store_[loc].first, store_[parent].first)) {
        std::swap(store_[parent], store_[loc]);
        trickleUp(parent);
    }

}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::heapify(int idx)
{
  if((m_*idx)+1 >= store_.size()) return;

  int smallerChild= (m_*idx)+1; // start w/ left
  int currChild;
  //iterate through all children
  for (int i = 1; i < m_; i++) {
    if (((m_*idx)+i) < store_.size()) {
      currChild = smallerChild+i;
    //if the currChild is less than the smallest,
    //make it the smallest
    if(c_(store_[currChild].first, store_[smallerChild].first))
      smallerChild = currChild;
    }
  }

  if(!(c_(store_[idx].first, store_[smallerChild].first))) {
    std::swap(store_[idx], store_[smallerChild]);
    heapify(smallerChild);
  } 
}


#endif

