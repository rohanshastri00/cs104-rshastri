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
        vector<Review*>::iterator review_dit;
 
    	for (product_dit = products.begin(); product_dit != products.end(); product_dit++)
    	{
    		delete product_dit->second;
    	}

    	for (user_dit = users.begin(); user_dit != users.end(); user_dit++)
    	{
    		delete user_dit->second;
    	}

        for (review_dit = all_reviews.begin(); review_dit != all_reviews.end(); review_dit++)
        {
            delete *review_dit;
        }

    }

    /**
     * Adds a product to the data store
     */
     //whenever u add a product, must update both product and keyword dbs
    void MyDataStore::addProduct(Product* p)
    {
    	products.insert(make_pair(convToLower(p->getName()), p));
    	//split the name of the product into words parseStringtoWords
        //for each word see if it exists add the product to the set of products. 
        //if it doesn't make a new pair, with a new key and a new set of products assoicated 
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
    	vector<Product*> cart;
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

        ofile << "<reviews>" << "\n";
        vector<Review*>::iterator v_it;

        for (v_it = all_reviews.begin(); v_it != all_reviews.end(); v_it++)
        {
            ofile << (*v_it)->prodName << '\n';
            ofile << (*v_it)->rating << " " << (*v_it)->username << " " << (*v_it)->date << " " << (*v_it)->reviewText;
            ofile << endl;
        }

        ofile << "</reviews>" << endl;


    }


    void MyDataStore::addToCart(string username, Product* p)
    {
 		map<string, vector<Product*> >::iterator map_it;

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

    	map<string, vector<Product*> >::iterator map_it;

 		//find given username in carts db
 		map_it = carts.find(username);
 		//if you cant find users
 		if (map_it == carts.end()) {
 			cout << "Invalid username" << endl;
 			return;
 		} 
 		vector<Product*> userCart = map_it->second;
 		vector<Product*> tempCart;
 		//check users for enoughMoney
 		map<string, User*>::iterator user_it = users.find(username);

		if (user_it == users.end()){
			cout << "Invalid username" << endl;
 			return;
		}

        for (unsigned int i = 0; i < userCart.size(); i++){

            if (userCart[i]->getQty() > 0  && 
                user_it->second->getBalance() > userCart[i]->getPrice()) {

                userCart[i]->subtractQty(1);
                user_it->second->deductAmount(userCart[i]->getPrice());   

                userCart.erase(userCart.begin());
            }
            else {
            //take the element at hand, pop it from the front and
            //add it to the back of temp list
                cout << userCart[i]->getName() << " was not purchased." << endl;
                Product* temp = userCart.front();
                userCart.erase(userCart.begin());
                tempCart.push_back(temp);
            }
    
        }
 		//userCart is now empty, push tempCart into user cart
 		for (unsigned int i = 0; i < tempCart.size(); i++){
 			userCart.push_back(tempCart.front());
 			tempCart.erase(tempCart.begin());
 		}
    }

    void MyDataStore::viewCart(string username)
    {
    	map<string, vector<Product*> >::iterator map_it;
 		//find given username in carts db
 		map_it = carts.find(username);
 		if (map_it == carts.end())
 		{
 			cout << "Invalid username" << endl;
 			return;
 		}


 		vector<Product*>::iterator vector_it;
 		vector_it = map_it->second.begin();

 		if (map_it->second.empty())
 		{
 			cout << "Cart is empty." << endl;
 			return;
 		}

 		int itemCount = 1;
 		while (vector_it != map_it->second.end())
 		{
 			cout << "Item " << itemCount << endl;
 			cout << (*vector_it)->displayString();
 			vector_it++;
 			itemCount++;
 		}

    }

    void MyDataStore::removeFromCart(User* u, Product* p)
    {
        string username = u->getName();
        map<string, vector<Product*> >::iterator cart_it = carts.find(username);
        vector<Product*>::iterator vector_it;

        if(cart_it->second.size() == 0)
        {
            return;
        }

        for (vector_it = cart_it->second.begin(); vector_it != cart_it->second.begin(); vector_it++)
        {
            if ((*vector_it)->getName() == p->getName())
            {
                cart_it->second.erase(vector_it);
                break;
            }
        } 
 
    }

    void MyDataStore::addReview(Review* r)
    {
        map<string, Product*>::iterator p_it;
        p_it = products.find(convToLower(r->prodName));
        //if review is not found in products db
        if (p_it == products.end())
        {
            all_reviews.push_back(r);
            return;
        }
 
        map<string, vector<Review*> >::iterator r_it;
        r_it = reviews.find(convToLower(p_it->first));
        //if product in the product db but not in review db i.e. first review
        if (r_it == reviews.end())
        {
            vector<Review*> newReviewSet;
            newReviewSet.push_back(r);
            reviews.insert(make_pair(p_it->first, newReviewSet));
            p_it->second->setRating((double)r->rating);   
        }
        else {
            r_it->second.push_back(r);
            vector<Review*> current = r_it->second;
            double total = 0;
            double numReviews = 0;

            for (unsigned int i = 0; i < current.size(); i++)
            {
                total += current[i]->rating;
                numReviews++;
            }
            double average = total/numReviews;
            p_it->second->setRating(average);
       }
        all_reviews.push_back(r);

    }

    vector<Review*> MyDataStore::getReview(Product* p)
    {

        map<string, vector<Review*> >::iterator r_it;
        r_it = reviews.find(convToLower(p->getName()));
        return r_it->second;
    }


    vector<User*> MyDataStore::getUserVector()
    {
        map<string, User*>::iterator u_it;
        vector<User*> user_vector;
        for (u_it = users.begin(); u_it != users.end(); u_it++)
        {
            user_vector.push_back(u_it->second);
        }

        return user_vector;
    }

    User* MyDataStore::getCurrentUser(string name)
    {
        map<string, User*>::iterator u_it = users.find(convToLower(name));
        //not possible to give an invalid username bc all names have been populated
        return u_it->second;
    }


    vector<Product*> MyDataStore::getCart(string name)
    {
        map<string, vector<Product*> >::iterator cart_it = carts.find(name);
        return cart_it->second;
    }





