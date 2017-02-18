#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "llistint.h"
#include <string>

using namespace std;

class LListTest : public testing::Test
{
	protected:
		LListTest() { }
		~LListTest() { }
		virtual void SetUp() 
		{
			list = new LListInt();
		}
		virtual void TearDown() 
		{ 
			list->clear();
			delete list;
		}
		LListInt* list;

};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListTest, Copy_Empty) 
{

	LListInt copy(*list);

	EXPECT_TRUE(copy.empty());
}

TEST_F(LListTest, Copy_AddFirstElement) 
{

	list->insert(0,6);

	LListInt copy(*list);

	EXPECT_TRUE(!copy.empty());
	EXPECT_EQ(copy.get(0),6);
}

TEST_F(LListTest, Copy_AddThreeElements) 
{

	list->insert(0,3);
	list->insert(1,4);
	list->insert(2,5);

	LListInt copy(*list);

	EXPECT_EQ(copy.get(0),3);
	EXPECT_EQ(copy.get(1),4);
	EXPECT_EQ(copy.get(2),5);
}



TEST_F(LListTest, Equals_Empty) 
{

	LListInt* copy = list;

	EXPECT_TRUE(copy->empty());
}

TEST_F(LListTest, Equals_AddFirstElement) 
{

	list->insert(0,6);
	LListInt* copy = list;

	EXPECT_TRUE(!copy->empty());
	EXPECT_EQ(copy->get(0),6);
}

TEST_F(LListTest, Equals_AddThreeElements) 
{

	list->insert(0,3);
	list->insert(1,4);
	list->insert(2,5);

	LListInt* copy = list;

	EXPECT_EQ(copy->get(0),3);
	EXPECT_EQ(copy->get(1),4);
	EXPECT_EQ(copy->get(2),5);
}

TEST_F(LListTest, PushBack_AddFromEmpty_ThreeElements) 
{

	list->push_back(3);
	list->push_back(4);
	list->push_back(5);

	EXPECT_TRUE(!list->empty());
	EXPECT_EQ(list->get(0),3);
	EXPECT_EQ(list->get(1),4);
	EXPECT_EQ(list->get(2),5);
}


TEST_F(LListTest, Concatenate) 
{

	LListInt mylist1;
	LListInt mylist2;  

	mylist1.insert(0,3);
	mylist1.insert(1,4);
	mylist1.insert(2,5);

	mylist2.insert(0,6);
	mylist2.insert(1,7);
	mylist2.insert(2,8);

	mylist1 += mylist2;

	EXPECT_EQ(mylist1.get(0),3);
	EXPECT_EQ(mylist1.get(3),6);
	EXPECT_EQ(mylist1.get(5),8);


}

TEST_F(LListTest, Concatenate_ThreeLists)
{

	LListInt mylist1;
	LListInt mylist2;  
	LListInt mylist3;

	mylist1.insert(0,3);
	mylist1.insert(1,4);
	mylist1.insert(2,5);

	mylist2.insert(0,6);
	mylist2.insert(1,7);
	mylist2.insert(2,8);

	mylist3.insert(0,9);
	mylist3.insert(1,10);
	mylist3.insert(2,11);

	mylist1 += mylist2 += mylist3;

	EXPECT_EQ(mylist1.get(0),3);
	EXPECT_EQ(mylist1.get(3),6);
	EXPECT_EQ(mylist1.get(6),9);
	EXPECT_EQ(mylist1.get(8),11);
}


TEST_F(LListTest, Output) 
{

	LListInt mylist1;

	for (int i = 0; i < 17; i++)
	{
		mylist1.insert(i, i+3);

	}

	ostringstream out;
 	out << mylist1;
 	string output = out.str(); 


  	EXPECT_EQ("3 4 5 6 7 8 9 10 11 12", output.substr(0,22));
  	//ignoring char 23 bc space from " "
  	EXPECT_EQ("13 14 15 16 17 18 19 ", output.substr(24, 35));
}


