#ifndef CLOTHING_H
#define CLOTHING_H
#include <string>
#include <iostream>
#include "product.h"
#include "util.h"

using namespace std;


class Clothing : public Product {
public:
	Clothing(string category, const string name, 
		double price, int qty, string size, string brand);

	~Clothing();

	set<string> keywords() const;

	string displayString() const;

	void dump(ostream& os) const;

protected:
	string size_;
	string brand_;
};


#endif