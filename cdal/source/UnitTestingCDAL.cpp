// UnitTestingCDAL.cpp : Defines the entry point for the console application.
//


#include "CDAL.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Testing methods that do not change the list"){
	CDAL<int> list;
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
		REQUIRE(list.contains(25, &CDAL<int>::equals_function) == true);
		REQUIRE(list.contains(50, &CDAL<int>::equals_function) == false);
		REQUIRE(list.contains(0, &CDAL<int>::equals_function) == true);
		REQUIRE(list.contains(49, &CDAL<int>::equals_function) == true);
	}
	
	CDAL<int> l(list);   //copy constructor
	REQUIRE (l.itemAt(26)==26);
	

}

TEST_CASE("PUSH/POP METHODS"){
	CDAL<int> list;
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
		REQUIRE(list.itemAt(499) == 499);
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
		for (int i = 6; i < 494; i++){
			int x=list.pop_front();
			REQUIRE(x == i);
		}
	}

	SECTION("POP_BACK"){
		for (int i = 0; i < 500; i++){
			list.push_back(i);
		}
		REQUIRE(list.pop_back() == 499);
		REQUIRE(list.pop_back() == 498);
		REQUIRE(list.pop_back() == 497);
		REQUIRE(list.pop_back() == 496);
		for (int i = 495; i !=430; i--){        
			int x = list.pop_back();  
			REQUIRE(x == i);
		}

	}
}


TEST_CASE("INSERT/REMOVE/REPLACE methods"){
	CDAL<int> list;
	for (int i = 0; i < 525; i++){
		list.push_back(i);
	}
	
	SECTION("INSERT"){
		list.insert(1000, 0);      //beginning of the list;
		list.insert(1000, 500);
		REQUIRE(list.itemAt(0) == 1000);
		REQUIRE(list.itemAt(500) == 1000);  //this
		

	}
	
	
	SECTION("REMOVE"){
		  REQUIRE(list.remove(20)==20);
		  REQUIRE(list.itemAt(20)==21);
		  REQUIRE(list.remove(523)==523);
		  REQUIRE(list.remove(522)==522);
		  REQUIRE(list.remove(521)==521);
		
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
	CDAL<int> list;
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
			flag = true;
		}
		REQUIRE(flag == true);
	}
} 


TEST_CASE("Exception Testing POP methods"){
	CDAL<int> list;
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
	CDAL<char> list;
	int k = 'a';
	for (int i = 0; i < 26; i++){
		list.push_back(k);
		k++;
	}
	list.clear();
	REQUIRE(list.isEmpty() == true);
}


TEST_CASE("Iterator testing"){
	CDAL<int> list;
	for (int i = 0; i < 120; i++){
		list.push_back(i);
	}

	CDAL<int>::iterator begin = list.begin();
	CDAL<int>::iterator end = list.end();

	REQUIRE(*begin == 0);

	begin++;
	REQUIRE(*begin==1);
	++begin;
	REQUIRE(*begin==2);
	
	REQUIRE(begin!=end);
	
	const CDAL<int> l=list;
	
	CDAL<int>::const_iterator b=l.begin();
	CDAL<int>::const_iterator e=l.end();
	
	REQUIRE(*b == 0);

	b++;
	REQUIRE(*b==1);
	++b;
	REQUIRE(*b==2);
	
	REQUIRE(b!=e);
	
	
}

TEST_CASE("More Iterator testing"){
	CDAL<int> list;
	for (int i = 0; i < 50; i++){
		list.push_back(i);
	}

}

TEST_CASE("Testing the [] operator"){
CDAL<int> list;

	for(int i=0;i<120;i++){
	list.push_back(i);
	}
	
	REQUIRE(list[0]==0);
	REQUIRE(list[119]==119);
	
	
const CDAL<int> l=list;
	REQUIRE(l[0]==0);
	REQUIRE(l[119]==119);


}