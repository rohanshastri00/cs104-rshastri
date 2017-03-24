#ifndef MSORT_H
#define MSORT_H

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "product.h"
#include "review.h"
#include <sstream>
#include <iterator>

using namespace std;

template <class T, class Comparator>
void msort(vector<T>&, vector<T>&, int, int, Comparator);


template <class T, class Comparator>
void merge(vector<T>&, vector<T>&, int, int, int, Comparator);

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp)
{

	if (myArray.size() == 1) return;
 
 	if (myArray.size() != 1)
 	{
    vector<T> copy(myArray);
 		msort(copy, myArray, 0, myArray.size()-1, comp);
 	}
}

template <class T, class Comparator>
void msort(vector<T>& myArray, vector<T>& output, int start, int end, Comparator comp)
{
  if (start>=end) {return;}
	//base 
  if (start < end)
  {
    int mid = start + (end - start) / 2; 
  	msort(myArray, output, start, mid, comp);
  	msort(myArray, output, mid+1, end, comp);
  	merge(myArray, output, start, mid, end, comp);
  }

}


template <class T, class Comparator>
void merge(vector<T>& myArray, vector<T>& output, int start, int mid, int end, Comparator comp)
{
  int s1 = start; 
  int e1 = mid;
  int s2 = mid + 1; 
  int e2 = end;

  int i = s1; 

  while ((s1 <= e1) && (s2 <= e2))
  {
    if (comp(myArray[s1], myArray[s2])) {
      output[i] = myArray[s1];
      s1++; 
    }
    else {
      output[i] = myArray[s2]; 
      s2++;
    } 
    i++;
  } 
  while (s1 <= e1) {
    output[i] = myArray[s1]; 
    s1++;
    i++;

  }
  while (s2 <= e2) {
    output[i] = myArray[s2]; 
    s2++;
    i++;
  } 
  for (i = start; i <= end; i++) {
    myArray[i] = output[i];
  }
}


template<class T>
struct AlphabetComp {
  bool operator()(const T& lhs, const T& rhs) {
    return (lhs)->getName() < (rhs)->getName();
  }
};

template<class T>
struct RatingComp {
  bool operator()(const T& lhs, const T& rhs) {
    return (lhs)->getAvgRating() > (rhs)->getAvgRating();
  }
};

template<class T>
struct DateComp {
  bool operator()(const T& lhs, const T& rhs) {
    string s1 = (lhs)->date;
    string s2 = (rhs)->date;

    string::iterator iter;
    for (iter = s1.begin(); iter != s1.end(); iter++) {
        if ( (*iter) == '-'){
          iter = s1.erase(iter);
        }
    }

    string::iterator iter2;
    for (iter2 = s2.begin(); iter2 != s2.end(); iter2++) {
        if ( (*iter2) == '-'){
          iter2 = s2.erase(iter2);
        }
    }

    stringstream convert1(s1);
    stringstream convert2(s2);

    int i1;
    int i2;

    convert1 >> i1;
    convert2 >> i2;

    return i1 < i2;
  }
};



#endif
