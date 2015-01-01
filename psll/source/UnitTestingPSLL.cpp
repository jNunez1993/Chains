// UnitTestingPSLL.cpp : Defines the entry point for the console application.
//


#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "PSLL.h"

TEST_CASE("Testing methods that do not change the list"){    
	PSLL<int> list; 
	for (int i = 0; i < 50; i++){     
		list.push_back(i);
	}

	SECTION("Size()"){
		REQUIRE(list.size() == 50);
	}
	SECTION("itemAt()"){
		REQUIRE(list.itemAt(26) == 26);
	}
	SECTION("isEmpty()"){
		REQUIRE(list.isEmpty() == false);
	}
	SECTION("Contains()"){
		REQUIRE(list.contains(25,&PSLL<int>::equals_function) == true);
		REQUIRE(list.contains(50, &PSLL<int>::equals_function) == false);
		REQUIRE(list.contains(0, &PSLL<int>::equals_function) == true);
		REQUIRE(list.contains(49, &PSLL<int>::equals_function) == true);
	}

}

TEST_CASE("PUSH/POP METHODS"){
	PSLL<int> list;
	SECTION("PUSH_FRONT"){
		list.push_front(10);
		list.push_front(9);
		list.push_front(3);
		REQUIRE(list.itemAt(0) == 3);
		REQUIRE(list.itemAt(2) == 10);
	}
	SECTION("PUSH_BACK"){
		for (int i = 0; i < 500; i++){
			list.push_back(i);
		}
		REQUIRE(list.itemAt(499)==499);
		REQUIRE(list.itemAt(0) == 0);
	}
	SECTION("POP_FRONT"){
		for (int i = 0; i < 500; i++){
			list.push_back(i);
		}
		REQUIRE(list.pop_front() == 0);
		REQUIRE(list.pop_front() == 1);
		REQUIRE(list.pop_front() == 2);
		REQUIRE(list.pop_front() == 3);
		REQUIRE(list.pop_front() == 4);
		REQUIRE(list.pop_front() == 5);
	}
	
	SECTION("POP_BACK"){
		for (int i = 0; i < 500; i++){
			list.push_back(i);
		}
		REQUIRE(list.pop_back() == 499);
		REQUIRE(list.pop_back() == 498);
		REQUIRE(list.pop_back() == 497);
		REQUIRE(list.pop_back() == 496);

	}
}


TEST_CASE("INSERT/REMOVE/REPLACE methods"){
	PSLL<int> list;
	for (int i = 0; i < 500; i++){
		list.push_back(i);
		REQUIRE(list.itemAt(i)==i);
	}
	SECTION("INSERT"){
		list.insert(1000, 0);      //beginning of the list;
		list.insert(1000, 501);   //one past element of the list;
		REQUIRE(list.itemAt(0) == 1000);
		REQUIRE(list.itemAt(list.size()-1) == 1000);
	}
	SECTION("REMOVE"){
		list.remove(0);      //removes first element
		list.remove(498);  //last position after first removal. 
		REQUIRE(list.itemAt(0) == 1);     //first position is now equal to what used to be the second element
		REQUIRE(list.itemAt(list.size()-1) == 498);
	}
	SECTION("REPLACE"){
		list.replace(1000, 499);
		REQUIRE(list.itemAt(499) == 1000);
		list.replace(1000, 0);
		REQUIRE(list.itemAt(0) == 1000); 
		REQUIRE(list.itemAt(1) == 1);
	}
}

TEST_CASE("EXCEPTION TESTING"){
	PSLL<int> list;
	for (int i = 0; i < 500; i++){
		list.push_back(i);
	}
	SECTION("REPLACE"){
		bool flag = false;
		try{
			list.replace(10, -1);
		}
		catch (out_of_range e){
			if (e.what() == "Invalid Position");
			flag = true;
		}
		REQUIRE(flag == true);
	}
	
	SECTION("INSERT"){
		bool flag = false;
		try{
			list.insert(1000, 505);
		}
		catch (out_of_range e){
			if (e.what() == "Invalid Position");
			flag = true;
		}
		REQUIRE(flag == true);
	}
	SECTION("REMOVE"){
		bool flag = false;
		try{
			list.remove(505);
		}
		catch (out_of_range e){
			if (e.what() == "Invalid Position");
			flag =true ;
		}
		REQUIRE(flag == true);
	}

}

TEST_CASE("Exception Testing POP methods"){
	PSLL<int> list;
	//empty list

	SECTION("POP_FRONT"){
		bool flag = false;

		try{
			list.pop_front();;
		}
		catch (exception e){
			if (e.what() == "List is Empty");
			flag = true;
		}
		REQUIRE(flag == true);
	}

	SECTION("POP_BACK"){
		bool flag = false;

		try{
			list.pop_back();;
		}
		catch (exception e){
			if (e.what() == "List is Empty");
			flag = true;
		}
		REQUIRE(flag == true);
	}

}
TEST_CASE("CLEAR METHOD"){
	PSLL<char> list;
	int k = 'a';
	for (int i = 0; i < 26; i++){
		list.push_back(k);
		k++;
	}
	list.clear();
	REQUIRE(list.isEmpty() == true);
}

TEST_CASE("Iterator testing"){
	PSLL<int> list;
	for (int i = 0; i < 50; i++){
		list.push_back(i);
	}

	PSLL<int>::iterator begin = list.begin();
	PSLL<int>::iterator end = list.end();

	REQUIRE(*begin == 0);
	int i = 0;
	while (i < list.size()-1){
		++begin;
		i++;
	}
	REQUIRE(*begin == 49);
	REQUIRE(*begin!=50);
	
	//const iterator
	const PSLL<int> l=list;
	PSLL<int>::const_iterator b=l.begin();
	PSLL<int>::const_iterator e=l.end();
	
	REQUIRE(*b == 0);
	i = 0;
	while (i < l.size()-1){
		++b;
		i++;
	}
	REQUIRE(*b == 49);
	REQUIRE(*b!=50);
}




TEST_CASE("More Iterator testing"){
PSLL<int> list;
	for (int i = 0; i < 50; i++){
		list.push_back(i);
	}

	PSLL<int>::iterator begin = list.begin();
	PSLL<int>::iterator end = list.end();
	
	begin++;
	REQUIRE(*begin==1);
	
	
	const PSLL<int> l(list);       //copy constructor for list class;
	PSLL<int>::const_iterator b=l.begin();
	PSLL<int>::const_iterator e=l.end();
	
	REQUIRE(*b == 0);
	b++;
	REQUIRE(*b == 1);
	
}
TEST_CASE("List [] operator"){
	PSLL<int> list;
	for (int i = 0; i < 50; i++){
		list.push_back(i);
	}

	REQUIRE(list[0] == 0);
	REQUIRE(list[25] == 25);
	REQUIRE(list[49] == 49);
	
	const PSLL<int> l = list;
	REQUIRE(list[0] == 0);
	REQUIRE(list[25] == 25);
	REQUIRE(list[49] == 49);


}



	