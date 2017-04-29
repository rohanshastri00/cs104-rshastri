#include <sstream>
#include <iomanip>
#include "clothing.h"
#include <iostream>
#include "util.h"

Clothing::Clothing(string category, const string name, 
		double price, int qty, string size, string brand):
	Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;

}

Clothing::~Clothing() { }

set<string> Clothing::keywords() const
{
	//keywords include name of clothing, size, or brand
	string toParser = name_ + " " + size_ + " " + brand_;
	return parseStringToWords(toParser);
}

string Clothing::displayString() const
{
	//convert price and qty to strings...
	ostringstream p, q;
	string price_string, quantity;

	p << price_;
	q << qty_;

	price_string = p.str();
	quantity = q.str();


	return  name_  +  "\n" + "Size: " + size_ + " Brand: " + brand_ 
	+ "\n" + price_string + " " + quantity + " left." + "\n";


}

void Clothing::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
	<< "\n" << size_ << "\n" << brand_ << endl;
}
