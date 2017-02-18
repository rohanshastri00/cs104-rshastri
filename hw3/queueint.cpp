#include "queueint.h"
#include <iostream>

using namespace std;


    /**
     * Default constructor - empty queue
     */
QueueInt::QueueInt() {}

    /**
     * Returns the current number of items in the queue in O(1)
     */
QueueInt::~QueueInt() 
{
    list.clear();
}
int QueueInt::size() const
{
    return list.size();
}

    /**
     * Returns true if the queue is empty, false otherwise in O(1)
     */
bool QueueInt::empty() const
{
    return list.empty();
}

    /**
     * Add to the back of the queue in O(1)
     */
void QueueInt::push(const int& val)
{
    list.push_back(val);
}

    /**
     * Removes the value at the front of the queue in O(1)
     */
void QueueInt::pop()
{
    list.remove(0);
}

    /**
     * Returns the value at the front of the queue  in O(1)
     */
int const & QueueInt::front() const
{
    return list.get(0);
}

    /**
     *  Concatenate the contents of the other queue
     *  to the back of this queue in O(1) leaving
     *  the other queue empty
     */
void QueueInt::concatenate(QueueInt& other)
{
    list += other.list;
}
