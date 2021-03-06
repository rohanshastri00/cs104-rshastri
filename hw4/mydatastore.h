#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"



using namespace std;
/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */

 //users, products, keywrods =  need database for each of them
 //later need it for carts
 //user and product databases are straightforward = maps
 //keyword map db is more complicated.. +1 dimension
class MyDataStore : public DataStore {
public:
    MyDataStore() { }

    //you dynamically allocated a bunch of proudcts with makeProduct()
    //gotta delete em
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    vector<Product*> search(vector<string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(ostream& ofile);

    void addToCart(string username, Product* p);

    void buyCart(string username);

    void viewCart(string username);


protected:
    //string means name of the product, Product* grabs deets of said prodct
    map<string, Product*> products;

    //string means name of user, User* grabs user info
    map<string, User*> users;

    //string is the keyword itself, set of products linked to that keyword
    map<string, set<Product*> > keywords;

    //key is the name of the user, with the value being a set of products
    map<string, deque<Product*> > carts;
};

#endif
