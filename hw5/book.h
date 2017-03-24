#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
#include "product.h"
#include "util.h"

using namespace std;


class Book : public Product {
public:
	Book(string category, const string name, 
		double price, int qty, string isbn, string author);
	~Book();

	set<string> keywords() const;

	string displayString() const;

	void dump(ostream& os) const;

protected:
	string isbn_;
	string author_;
};


#endif