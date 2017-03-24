#Rohan Shastri

#HW5 CSCI 104

#March 24th, 2017

#AMAZON GUI

Graphical user interface in order
to search, add to cart, and purchase
items from a database.

Enter
qmake -project
qmake
make
in terminal to create 
an executable for the program. Must 
include a database as an arguement 
in order to run succesfully

make clean removes the object file 
created for amazon


#mydatastore.cpp

Creates all 4 necessary databases to 
keep track of products, users, keywords,
and user carts. Derived from datastore.h

#main_window.cpp

Wraps mydatastore instance in GUI, once
running the program is intuitive 