#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include <limits>

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

                //userCart.erase(userCart.begin());
                removeFromCart(user_it->second, userCart[i]->getName());
            }
            else {
            //take the element at hand, pop it from the front and
            //add it to the back of temp list
                cout << userCart[i]->getName() << " was not purchased." << endl;
                Product* temp = userCart.front();
                //userCart.erase(userCart.begin());
                removeFromCart(user_it->second, userCart[i]->getName());

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

void MyDataStore::removeFromCart(User* u, string productname)
{
        string username = u->getName();
        map<string, vector<Product*> >::iterator cart_it = carts.find(username);
        vector<Product*> products = cart_it->second;

        if(cart_it->second.size() == 0) {
            return;
        }
        for (unsigned int i = 0; i < products.size();i++) {
            if (products[i]->getName() == productname) {
                cart_it->second.erase(cart_it->second.begin() + i);
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


map<string, User*> MyDataStore::getUserDatabase()
{
    return users;
}


bool MyDataStore::userExists(string username)
{
    map<string, User*>::iterator user_it = users.find(username);
    if (user_it != users.end()){
        //user exists in db
        return true;
    }
    return false;
}


Product* MyDataStore::findProduct(string product_name)
{
    map<string, Product*>::iterator prod_it = products.find(product_name);
    return prod_it->second;
}


void MyDataStore::calculateSimilarities()
{
    double sim_score = 0;
    double average = 0;
    int counter = 0;
    //it through all reviews
    for (unsigned int i = 0; i < all_reviews.size(); i++) {
        string first = all_reviews[i]->username;
        for (unsigned int j = 1; j < all_reviews.size(); j++) {
            string second = all_reviews[j]->username;
            //if reviewing same product and users are not the same
            if ((all_reviews[i]->prodName == all_reviews[j]->prodName) && (first != second)) {
                //check if user has already been added to neighbors_scores
                //it has not
                sim_score = abs(all_reviews[i]->rating - all_reviews[j]->rating)/4.0;
                if (sim_score >= 1) { continue; }

                counter++;

                if (neighbors_scores.find(first) == neighbors_scores.end()) {
                    map<string, double> temp;
                    temp.insert(make_pair(second, sim_score));
                    neighbors_scores.insert(make_pair(first, temp));
                }
                else { //user exists in the neighbors_scores
                    map<string, map<string, double> >::iterator map_it = neighbors_scores.find(first);
                    map_it->second.insert(make_pair(second, sim_score));
                }
            }
            average += sim_score;
        }
        average = average/counter;
        basic_sim.insert(make_pair(first, average));
    }
}


map<string, double> MyDataStore::dijkstra(string username)
{
    calculateSimilarities();
    Heap<string> minHeap;
    map<string, double> solution;
    solution.insert(make_pair(username, 0));
    minHeap.push(0.0, username);

    map<string, map<string, double> >::iterator first_it = neighbors_scores.begin();
    // push all vertices into heap
    for (; first_it != neighbors_scores.end(); ++first_it) {
        solution.insert(make_pair(first_it->first, numeric_limits<double>::infinity()));        
        minHeap.push(numeric_limits<double>::infinity(), first_it->first);
    }

    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!(minHeap.empty()))
    {
        // Extract the vertex with minimum distance value
        string currNode = minHeap.top();
        minHeap.pop();

        map<string, double > neighbors = neighbors_scores.find(currNode)->second;
        map<string, double >::iterator second_it = neighbors.begin();
        for (; second_it != neighbors.end(); ++second_it) {
            //if a neighbor is in the heap
            if (solution.find(second_it->first) != solution.end() ) {

                double current_val = neighbors.find(currNode)->second;
                double neighbor_val = neighbors.find(second_it->first)->second;
                double heap_val = solution.find(second_it->first)->second; 

                if ((current_val + neighbor_val) < heap_val) {
                    minHeap.decreaseKey(neighbor_val + current_val, currNode);
                    //finding name in solution, updating value
                    solution[second_it->first] = current_val + neighbor_val;
                }
            }
        }
    }
    return solution;
}


vector<pair<string, double> > MyDataStore::makeSuggestion(string currentUser) 
{
    dijkstra(currentUser);
    vector<pair<string, double> > recommendations;
    //map of products corresponding to a set of reviews for that product
    map<string, set<Review*> > prods_to_users;

    //find the products the currUser has reviewed
    set<string> reviewed_prods;
    for (unsigned int i = 0; i < all_reviews.size(); i++) {
        if (all_reviews[i]->username == currentUser) {
            reviewed_prods.insert(all_reviews[i]->prodName);
        }
    }

    //building prods_to_users
    for (unsigned int i = 0; i < all_reviews.size(); i++) {
        //if currUser has not reviewd the product 
        if (reviewed_prods.find(all_reviews[i]->prodName) == reviewed_prods.end()) {
            // if the same product is also not prods_to_users
            if (prods_to_users.find(all_reviews[i]->prodName) == prods_to_users.end()) {
                //make a new set of reviews, insert the new review, add to db
                set<Review*>tempSet;
                tempSet.insert(all_reviews[i]);
                prods_to_users.insert(make_pair(all_reviews[i]->prodName, tempSet));
            }
            else {
                //add the review to existing set for that product
                prods_to_users[all_reviews[i]->prodName].insert(all_reviews[i]);
            }
        }
    }
    
    //iterate through prods to users to find recs based on similarity
    map<string, set<Review*> >::iterator map_it; 
    for (map_it = prods_to_users.begin(); map_it != prods_to_users.end(); map_it++) {
        //get the neighbors and their scores for currUser
        map<string, double> neighbors = neighbors_scores.find(currentUser)->second;
        double RP = 0;
        double W = 0;
        set<Review*>::iterator set_it = map_it->second.begin();
        for (; set_it != map_it->second.end(); set_it++) {
            double user_rating = neighbors.find((*set_it)->username)->second;
            RP += ((1 - user_rating) * ((*set_it)->rating));
            W += (1 - user_rating);
        }
        if (W == 0) {
            recommendations.push_back(make_pair(map_it->first, 0));
            break;
        }
        else {
            double sum = RP / W;
            recommendations.push_back(make_pair(map_it->first, sum));
        }
    }
    return recommendations;
}