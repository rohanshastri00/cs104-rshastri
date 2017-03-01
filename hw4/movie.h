#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>
#include "product.h"
#include "util.h"


using namespace std;


class Movie : public Product {
public:
	Movie(string category, const string name, 
		double price, int qty, string genre, string rating);

	~Movie();

	set<string> keywords() const;

	string displayString() const;

	void dump(ostream& os) const;

protected:
	string genre_;
	string rating_;
};


#endif