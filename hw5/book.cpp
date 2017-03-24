#include <sstream>
#include <iomanip>
#include "book.h"
#include <iostream>
#include "util.h"

using namespace std;

Book::Book(string category, const string name, 
		double price, int qty, string isbn, string author):
	Product(category, name, price, qty)
{
	isbn_ = isbn;
	author_ = author;

}
Book::~Book() { }

set<string> Book::keywords() const
{
	//keywords include name of book, author, or IBSN
	string toParser = name_ + " " + author_ + " " + isbn_;
	return parseStringToWords(toParser);
}

string Book::displayString() const
{
	//convert price and qty to strings...
	ostringstream p, q;
	string price_string, quantity;

	p << price_;
	q << qty_;

	price_string = p.str();
	quantity = q.str();


	return  name_  +  "\n" + "Author: " + author_ + " ISBN: " + isbn_ 
	+ "\n" + price_string + " " + quantity + " left." + "\n";
}

void Book::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
	<< "\n" << isbn_ << "\n" << author_ << endl;

}