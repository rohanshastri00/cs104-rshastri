#include <sstream>
#include <iomanip>
#include "movie.h"
#include <iostream>
#include "util.h"

Movie::Movie(string category, const string name, 
		double price, int qty, string genre, string rating):
	Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;

}

Movie::~Movie() { }

set<string> Movie::keywords() const
{
	//keywords include name of movie, genre, and rating
	string toParser = name_ + " " + genre_ + " " + rating_;
	return parseStringToWords(toParser);
}

string Movie::displayString() const
{
	//convert price and qty to strings...
	ostringstream p, q;
	string price_string, quantity;

	p << price_;
	q << qty_;

	price_string = p.str();
	quantity = q.str();

	return  name_  +  "\n" + "Genre: " + genre_ + " Rating: " + rating_ 
	+ "\n" + price_string + " " + quantity + " left." + "\n";

}

void Movie::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_
	<< "\n" << genre_ << "\n" << rating_ << endl;
}