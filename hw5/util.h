#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

using namespace std;

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename set<T>::iterator it_1;
	typename set<T>::iterator it_2;

	set<T> intersection;

	for (it_1 = s1.begin(); it_1 != s1.end(); it_1++)
	{
		for (it_2 = s2.begin(); it_2 != s2.end(); it_2++)
		{
			//if the values equal eachother 
			if ((*it_1) == (*it_2))
			{
				intersection.insert((*it_1));
			}
		}
	}

	return intersection;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

	typename set<T>::iterator it_1;
	typename set<T>::iterator it_2;
	set<T> unionSet;


	for (it_1 = s1.begin(); it_1 != s1.end(); it_1++)
	{
		unionSet.insert((*it_1));
	}

	for (it_2 = s2.begin(); it_2 != s2.end(); it_2++)
	{
		unionSet.insert((*it_2));
	}
	
	return unionSet;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
