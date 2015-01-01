// UnitTestingSDAL.cpp : Defines the entry point for the console application.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SDAL.h"

//the function sizeofarray is a function that I included to demonstrate how the list shrinks and grows. It is included in testing size section and remove
//section where I thoroughly demonstrate the list growing and shrinking

TEST_CASE("TESTING PUSH"){
	SDAL<int> list;
	SECTION("PUSH_FRONT"){
		for (int i = 0; i < 500; i++){
			list.push_front(i);
			REQUIRE(list.itemAt(0)==i);
		}
		REQUIRE(list.itemAt(0) == 499);
		REQUIRE(list.itemAt(499) == 0);
		REQUIRE(list.size() == 500);

	}
	SECTION("PUSH_BACK"){
		for (int i = 0; i < 500; i++){
			list.push_back(i);
		}
		REQUIRE(list.itemAt(0) == 0);
		REQUIRE(list.itemAt(499) == 499);
		REQUIRE(list.size() == 500);
	}
}

TEST_CASE("TESTING POP"){
	SDAL<int> list;
	for (int i = 0; i < 75; i++){
		list.push_back(i);
	}
	
	SECTION("POP_FRONT"){
		REQUIRE(list.size() == 75);
		int k = list.pop_front();       
		REQUIRE(k == 0);
		REQUIRE(list.size() == 74);
		for (int i = 0; i < 15; i++){
			list.pop_front();
		}
		REQUIRE(list.size() == 59);
		REQUIRE(list.itemAt(0) == 16);
		list.pop_front();
		REQUIRE(list.size() == 58);     
	}
	
	
	SECTION("POP_BACK"){
		REQUIRE(list.size() == 75);
		int k = list.pop_back();
		REQUIRE(k == 74);
		REQUIRE(list.size() == 74);
		for (int i = 0; i < 73; i++){
			list.pop_back();
		}
		REQUIRE(list.size() == 1);
		list.pop_back();
		REQUIRE(list.size() == 0);
	}
	
	}

TEST_CASE("TESTING REPLACE/INSERT/REMOVE"){
	SDAL<char> list;
	char k = 'a';

	for (int i = 1; i <= 26; i++){
		list.push_back(k);
		k++;
	}

	REQUIRE(list.itemAt(0) == 'a');
	REQUIRE(list.itemAt(14) == 'o');
	REQUIRE(list.itemAt(25) == 'z');

	SECTION("REPLACE"){
		list.replace('E', 0);
		list.replace('E', 14);
		list.replace('E', 25);
		REQUIRE(list.itemAt(0) == 'E');
		REQUIRE(list.itemAt(14) == 'E');
		REQUIRE(list.itemAt(25) == 'E');
	}
	SECTION("INSERT"){
		REQUIRE(list.size() == 26);
		list.insert('E', 0);
		REQUIRE(list.size() == 27);
		list.insert('E', 27); //inserts new element at the end of the list;
		REQUIRE(list.size() == 28);
		REQUIRE(list.itemAt(0) == 'E');
		REQUIRE(list.itemAt(27) == 'E');
		REQUIRE(list.size() == 28);
		for (int i = 1; i <= 23; i++){  //extending the list with inserts;
			list.insert('X',28);
		}
		REQUIRE(list.size() == 51);
		REQUIRE(list.sizeofArray() == 75);
	}
	
	
	SECTION("REMOVE"){
		list.remove(0);
		REQUIRE(list.size() == 25);
		REQUIRE(list.itemAt(0) == 'b');
		list.remove(24);
		REQUIRE(list.size() == 24);

		SDAL<int> list1;                 //TESTING how the array shrinks when elements are removed.
		for (int i = 1; i <= 100; i++){
			list1.push_back(i);
		}
		REQUIRE(list1.size() == 100);
		REQUIRE(list1.sizeofArray() == 112);
		for (int i = 0; i <= 43; i++){
			list1.remove(i);
		}
		REQUIRE(list1.size() == 56);
		REQUIRE(list1.sizeofArray() == 112);
		list1.remove(0);
		REQUIRE(list1.size() == 55);
		REQUIRE(list1.sizeofArray() == 56);
	}
	
	
}

TEST_CASE("TESTING SIZE"){
	SDAL<int> list;

	SECTION("TEST 1"){
		REQUIRE(list.size() == 0);
		REQUIRE(list.sizeofArray() == 50);
	}

	SECTION("TEST 2"){
		for (int i = 1; i <= 50; i++){
			list.push_back(i);
		}
		REQUIRE(list.size() == 50);
		REQUIRE(list.sizeofArray() == 50);
	}
	SECTION("TEST 3"){
		for (int i = 1; i <= 51; i++){
			list.push_back(i);
		}
		REQUIRE(list.size() == 51);
		REQUIRE(list.sizeofArray() == 50 * 1.5);
	}

	SECTION("TEST 4"){
		int size = 75 * 1.5;
		for (int i = 1; i <= 76; i++){
			list.push_back(i);
		}
		REQUIRE(list.size() == 76);
		REQUIRE(list.sizeofArray() == size);
	}

	SECTION("TEST 5"){

		for (int i = 1; i <= 100; i++){      //pushed in 100 elements into the list
			list.push_back(i);
		}
		REQUIRE(list.size() == 100);         //as it should be, the amount of elements in the list should be 100
		REQUIRE(list.sizeofArray() == 112);  //the total arrSize should be 112 because the list expands from 50 to 75 to 112.

		for (int i = 1; i <= 45; i++){        //popped out 45 elements meaning that the list will now contain 55 elements
			list.pop_back();
		}
		REQUIRE(list.size() == 55);
		REQUIRE(list.sizeofArray() == 56);    //since the list had a maximum size of 112 and less than half of the slots are being used
		// then it shrinks in half
		for (int i = 1; i <= 2; i++){
			list.push_back(i);
		}
		REQUIRE(list.size() == 57);       //once the list has to expand again, it goes from 56 to 84 because it's increased by 1.5 times.
		REQUIRE(list.sizeofArray() == 84);
	}
	
}


TEST_CASE("TESTING CLEAR"){
	SDAL<int> list;
	char k = 'a';

	for (int i = 1; i <= 26; i++){
		list.push_back(k);
		k++;
	}
	REQUIRE(list.itemAt(0) == 'a');
	REQUIRE(list.itemAt(25) == 'z');

	list.clear();

	REQUIRE(list.size() == 0);
}

TEST_CASE("TESTING CONTAINS"){
	SDAL<int> list;
	for (int i = 1; i <= 120; i++){
		list.push_back(i);
	}

	REQUIRE(list.contains(1, &SDAL<int>::equals_function)==true);
	REQUIRE(list.contains(20, &SDAL<int>::equals_function) == true);
	REQUIRE(list.contains(120, &SDAL<int>::equals_function) == true);
	REQUIRE(list.contains(121, &SDAL<int>::equals_function) == false);
	REQUIRE(list.contains(0, &SDAL<int>::equals_function) == false);
}

TEST_CASE("Testing isEmpty()"){
	SDAL<int> list;

	REQUIRE(list.isEmpty() == true);
	
	list.push_back(1);
	REQUIRE(list.isEmpty() == false);
	
	for (int i = 0; i < 49; i++){
		list.push_back(i);
	}
	REQUIRE(list.isEmpty() == false);
	
	list.push_front(10);
	REQUIRE(list.isEmpty() == false);

	list.push_front(20);
	REQUIRE(list.isEmpty() == false);

	list.clear();
	REQUIRE(list.isEmpty() == true);
	
}

TEST_CASE("ITERATOR TESTING"){
	SDAL<int> list;
	for (int i = 1; i <= 500; i++){
		list.push_back(i);
	}
	SDAL<int>::iterator begin = list.begin();
	SDAL<int>::iterator end = list.end();

	REQUIRE(*begin == 1);
	
	begin++;
	REQUIRE(*begin == 2);
	
	const SDAL<int> l = list;
	SDAL<int>::const_iterator b = l.begin();
	SDAL<int>::const_iterator e = l.end();
	
	REQUIRE(*b == 1);
	b++;
	REQUIRE(*b==2);

}

TEST_CASE("MORE ITERATOR TESTING"){
SDAL<int> list;
	for (int i = 1; i <= 500; i++){
		list.push_back(i);
	}
	SDAL<int>::iterator begin = list.begin();
	SDAL<int>::iterator end = list.end();
	
	REQUIRE((begin!=end)==true);
	++begin;  //pre increment
	REQUIRE(*begin==2);
	
	const SDAL<int> l=list;
	
	SDAL<int>::const_iterator b = l.begin();
	SDAL<int>::const_iterator e = l.end();
	REQUIRE((begin!=end)==true);
	++b;  //pre increment
	REQUIRE(*b==2);
	++b;
	REQUIRE(*b==3);
	
}

TEST_CASE("TESTING THE [] OPERATOR"){
SDAL<int> list;
	for (int i = 0; i < 50; i++){
		list.push_back(i);
	}

	REQUIRE(list[0] == 0);
	REQUIRE(list[25] == 25);
	REQUIRE(list[49] == 49);

	const SDAL<int> l = list;
	REQUIRE(list[0] == 0);
	REQUIRE(list[25] == 25);
	REQUIRE(list[49] == 49);


}
