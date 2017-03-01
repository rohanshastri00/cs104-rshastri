#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"
#include "mydatastore.h"


using namespace std;


    //you dynamically allocated a bunch of proudcts with makeProduct()
    //gotta delete em
    MyDataStore::~MyDataStore()
    {
    	map<string, Product*>::iterator product_dit;
    	map<string, User*>::iterator user_dit;
 
    	for (product_dit = products.begin(); product_dit != products.end(); product_dit++)
    	{
    		delete product_dit->second;
    	}

    	for (user_dit = users.begin(); user_dit != users.end(); user_dit++)
    	{
    		delete user_dit->second;
    	}

    }

    /**
     * Adds a product to the data store
     */
     //whenever u add a product, must update both product and keyword dbs
    void MyDataStore::addProduct(Product* p)
    {
    	products.insert(make_pair(convToLower(p->getName()), p));


    	//update keyword dbs
    	//adding this product right? so split the name of the product into words
    	//parseStringtoWords, then for each word see if it exists in the keyword
    	//database. if it exists, boom add the product to the set of products. if
    	//it doesn't make a new pair, with a new key and a new set of products assoicated 
    	//with said keyword

    	string pName = p->getName();
    	 			//cout << "pName: " << pName <<  endl;
    	set<string> pNameKeywords = parseStringToWords(convToLower(pName));

    	set<string>::iterator set_it;
  		map<string, set<Product*> >::iterator map_it;

    	for (set_it = pNameKeywords.begin(); set_it != pNameKeywords.end(); set_it++)
    	{

    			//cout << "set_it: " << (*set_it) << endl;
    			map_it = keywords.find((*set_it));

    			//if the keyword from the product name matches any existing keywords
    			if (map_it != keywords.end())
    			{
    				//add product p to the set of products that matches the keyword
    				//cout << "keywords db pair updated" << endl;
    				map_it->second.insert(p);
    			}
    			else 
    			{
    				// make a new pair, with a new key and a new set of products assoicated 
    				//with said keyword
    				set<Product*>pSet;
    				pSet.insert(p);
    				keywords.insert(make_pair((*set_it), pSet));
    				//cout << "keywords db pair added" << endl;

    			}
    	}
    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u)
    {
    	users.insert(make_pair(convToLower(u->getName()), u));

    	//errtime u create a new user, u wanna make a new 
    	//cart for them too
    	deque<Product*> cart;
    	carts.insert(make_pair(convToLower(u->getName()), cart));


    }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    vector<Product*> MyDataStore::search(vector<string>& terms, int type)
    {

    	//iterate through the product db
    	vector<Product*> hits;
     	map<string, set <Product*> >::iterator map_it = keywords.begin();

     	set<Product*> set1;
     	set<Product*> set2;

     	set<Product*>::iterator set_it;

     	//if terms is empty
     	if (terms.size() == 0)
     	{
     		return hits;
     	}
     	//get the set for the first term
     	set1 = keywords.find(terms[0])->second;


     	//if set1 is empty, i.e. term not found
     	if (set1 == keywords.end()->second && type == 0)
     	{
     		cout << "No results found." << endl;
     		return hits;
     	}

     	//if there is only 1 term
        if (terms.size() == 1)
     	{
     		//if set1 didn't return anything
     		if (set1 == keywords.end()->second)
     		{
     			cout << "No results found." << endl;
     			return hits;
     		}
	     	for (set_it = set1.begin(); set_it != set1.end(); set_it++)
		    {
		    	hits.push_back(*set_it);
		    }
     		return hits;
     	}

     	//get set for the second term
	    for(unsigned int i = 1; i < terms.size();i++)
	    {

	    	set2 = keywords.find(terms[i])->second;
	    	//if set2 didnt return searches
	    	if (set2 == keywords.end()->second)
	    	{	
	    		//AND search, you don't want any results to show up
	    		if (type == 0)
	    		{
	    			cout << "No results found." << endl;
	    			return hits;
	    		}
	    		//OR search, you may want more results to show up
	    		if (type == 1)
	    		{	//if you've reached the last term
	    			if (i == terms.size()-1)
	    			{
	    				//if set1 is not empty
	    				if (set1 != keywords.end()->second)
	    				{
		    				for (set_it = set1.begin(); set_it != set1.end(); set_it++)
		    				{
		    					hits.push_back(*set_it);
		    				}

	    				return hits;
	    				}
	    				//if set1 is also empty then we didn't find anything
	    				else 
	    				{
	    					cout << "No results found." << endl;
	    					return hits;
	    				}
	    			}
	    			//if not the last term, break and go to the next element
	    			continue;
	    		}
	    	}
	    		//compare the sets
	    		//AND
	    		if (type == 0)
	    		{
	    			set1 = setIntersection(set1, set2);
	    		}
	    		//OR
	    		if (type == 1)
	    		{ 
	    			set1 = setUnion(set1, set2);
	    		}
	    	
	    }


	    for (set_it = set1.begin(); set_it != set1.end(); set_it++)
	    {
	    	hits.push_back(*set_it);
	    }

	    if (hits.empty())
	    {
	    	cout << "No results found." << endl;
	    }
    	return hits;
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(ostream& ofile)
    {
    	ofile << "<products>" << "\n";

    	map<string, Product* >::iterator map_it;

    	for (map_it = products.begin(); map_it != products.end();map_it++)
    	{    		
    		map_it->second->dump(ofile);
    	}
    	ofile << "</products>" << "\n";


    	ofile << "<users>" << "\n";
    	map<string, User* >::iterator map_it2;

    	for (map_it2 = users.begin(); map_it2 != users.end(); map_it2++)
    	{
    		map_it2->second->dump(ofile);
    	}

    	ofile << "</users>" << endl;

    }


    void MyDataStore::addToCart(string username, Product* p)
    {
 		map<string, deque<Product*> >::iterator map_it;

 		//find given username in carts db
 		map_it = carts.find(username);
 		//if you cant find users
 		if (map_it == carts.end())
 		{
 			cout << "Invalid username" << endl;
 			return;
 		}
 		//found the right user, now put the product in the back of 
 		//his/her cart
 		map_it->second.push_back(p);

    }

    void MyDataStore::buyCart(string username)
    {

    	map<string, deque<Product*> >::iterator map_it;

 		//find given username in carts db
 		map_it = carts.find(username);
 		//if you cant find users
 		if (map_it == carts.end())
 		{
 			cout << "Invalid username" << endl;
 			return;
 		} 

 		deque<Product*> userCart = map_it->second;
 		deque<Product*> tempCart;

 		deque<Product*>::iterator deque_it;

 		//check users for enoughMoney
 		map<string, User*>::iterator user_it;

		user_it = users.find(username);

		if (user_it == users.end())
		{
			cout << "Invalid username" << endl;
 			return;
		}

 		//user exists, so iterate through the deque, check
 		for (deque_it = userCart.begin(); deque_it != userCart.end(); deque_it++)
 		{
 			//find the user in question
 		 	
 		 	//if inStock && if they have enough credit
 		 	if ((*deque_it)->getQty() > 0 && 
 		 		user_it->second->getBalance() > (*deque_it)->getPrice())
 		 	{
 				//1. remove from cart
 				//2. reduce stock quantity by 1
 				//3. cost debited from user's credit
 				userCart.pop_front();
 		 		//^APPARENTLY THIS DOESNT DO ANYTHING?

 				(*deque_it)->subtractQty(1);

 				//deduct money from user credit
 				user_it->second->deductAmount((*deque_it)->getPrice());
 		 	}
 		 	else 
 		 	{
 		 	//take the element at hand, pop it from the front and
 		 	//add it to the back of temp list
 		 	cout << (*deque_it)->getName() << " was not purchased." << endl;
 		 	tempCart.push_back(userCart.front());
 		 	userCart.pop_front();
 		 	}
 	
 		}

 		//userCart is now empty, push tempCart into user cart
 		for (unsigned int i = 0; i < tempCart.size(); i++)
 		{
 			userCart.push_back(tempCart.front());
 			tempCart.pop_front();
 		}
    }

    void MyDataStore::viewCart(string username)
    {
    	map<string, deque<Product*> >::iterator map_it;
 		//find given username in carts db
 		map_it = carts.find(username);
 		if (map_it == carts.end())
 		{
 			cout << "Invalid username" << endl;
 			return;
 		}


 		deque<Product*>::iterator deque_it;
 		deque_it = map_it->second.begin();

 		if (map_it->second.empty())
 		{
 			cout << "Cart is empty." << endl;
 			return;
 		}

 		int itemCount = 1;
 		while (deque_it != map_it->second.end())
 		{
 			cout << "Item " << itemCount << endl;
 			cout << (*deque_it)->displayString();
 			deque_it++;
 			itemCount++;
 		}

    }


