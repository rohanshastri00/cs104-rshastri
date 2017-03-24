#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <cctype> 

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

    set<string>splitWords;
    string ssWord;
    string tempWord;

    stringstream ss(rawWords);

    while (ss >> ssWord)
    {
        for (unsigned i = 0; i <= ssWord.length(); i++)
        {
            //if i equals the length of ssWord it will be a space
            //bc of the way sstream works
            if (ispunct(ssWord[i]) || i == ssWord.length())
            {   
                //if it's not greater than two we don't want it
                if (tempWord.length() >= 2)
                {            
                    splitWords.insert(tempWord);
                }
                tempWord.clear();
            }
            else 
            {

                tempWord += ssWord.substr(i,1);
            }
        }
    }

    //what if they passed in men

    return splitWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
