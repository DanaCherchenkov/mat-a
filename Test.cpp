#include "doctest.h"
#include "mat.hpp"
#include <ctime>
using namespace ariel;
using namespace std;

string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input; 
}
//---------------------Good input---------------------------------

TEST_CASE("Positive and different numbers") {
	CHECK(nospaces(mat(9, 7, '@', '-')) == nospaces("@@@@@@@@@\n"
							"@-------@\n"
							"@-@@@@@-@\n"
							"@-@---@-@\n"
							"@-@@@@@-@\n"
							"@-------@\n"
							"@@@@@@@@@"));

    CHECK(nospaces(mat(5, 3, '@', '-')) == nospaces("@@@@@\n"
						"@-@-@\n"
						"@@@@@\n"));

	CHECK(nospaces(mat(13, 5, '%', '-')) == nospaces("%%%%%%%%%%%%%\n"
							 "%-----------%\n"
							 "%-%%%%%%%%%-%\n"
							 "%-----------%\n"
							 "%%%%%%%%%%%%%"));
	
	CHECK(nospaces(mat(3, 5, '$', '+')) == nospaces("$$$\n"
							"$+$\n"
							"$+$\n"
							"$+$\n"
							"$$$"));

	CHECK(nospaces(mat(1, 1, '@', '-')) == nospaces("@"));
}


TEST_CASE("Positive and identical numbers"){
	CHECK(nospaces(mat(11, 11, '%', '-')) == nospaces("%%%%%%%%%%%\n"
							"%-%%%%%%%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%-----%-%\n"
							"%-%%%%%%%-%\n"
							"%%%%%%%%%%%\n"));

	CHECK(nospaces(mat(9, 9, '@', '-')) == nospaces("@@@@@@@@@\n"
							"@-------@\n"
							"@-@@@@@-@\n"
							"@-@---@-@\n"
							"@-@---@-@\n"
							"@-@---@-@\n"
							"@-@@@@@-@\n"
							"@-------@\n"
							"@@@@@@@@@"));

    CHECK(nospaces(mat(5, 5, '$', '-')) == nospaces("$$$$$\n"
						"$-$-$\n"
						"$-$-$\n"
						"$-$-$\n"
						"$$$$$\n"));

}

//Good input - smooth carpet 
TEST_CASE("Positive numbers with identical chars"){
    CHECK(nospaces(mat(5, 5, '$', '$')) == nospaces("$$$$$\n"
						"$$$$$\n"
						"$$$$$\n"
						"$$$$$\n"
						"$$$$$\n"));

	CHECK(nospaces(mat(3, 7, '^', '^')) == nospaces("^^^\n"
							"^^^\n"
							"^^^\n"
							"^^^\n"
							"^^^\n"
							"^^^\n"
							"^^^\n"));
												
}


//---------------------Bad input---------------------------------


/* 
	Bad case if the numbers we get are even - need to have odd numbers to solve the problem
*/
TEST_CASE("even numbers") {
	srand((unsigned) time(0));
	int randomNum1, randomNum2;
	for( int i = 1; i < 50; i++){

		//range of[0,100]
		randomNum1 = (int)(rand() % 100);
		randomNum2 = (int)(rand() % 100);
		int num1 = randomNum1;
		int num2 = randomNum2;

		if ((num1 % 2 == 0) && (num2 % 2 == 0)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}

		if ((num1 % 2 == 0) || (num2 % 2 != 0)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}

		if ((num1 % 2 != 0) || (num2 % 2 == 0)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}

		//Check if the numbers obtained are consecutive
		if ((num2 == num1 + 1) || (num1 == num2 + 1)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}
	}
}


/* 
	Bad case - if we get a digit smaller then zero
*/
TEST_CASE ("negative numbers") {
	srand((unsigned) time(0));
	int randomNum1, randomNum2;
	for( int i = 1; i < 50; i++){

		//range of[-100,0]
		randomNum1 = (int)(rand() % 100) - 100;
		randomNum2 = (int)(rand() % 100) - 100;
		int num1 = randomNum1;
		int num2 = randomNum2;

		CHECK_THROWS(mat(num1, num2, '@', '-'));
	}
}


/* 
	Bad case - too big input will not be valid (if it contains more then 8 digits).
*/
TEST_CASE ("Too big input") {
	srand((unsigned) time(0));
	int randomNum1, randomNum2;
	for( int i = 1; i < 50; i++){

		//range of[0, infinity] -> 0x7FFF is the max value
		randomNum1 = (int)(rand() % 0x7FFF);
		randomNum2 = (int)(rand() % 0x7FFF);
		int num1 = randomNum1;
		int num2 = randomNum2;

		if ((num1 > 10000000) && (num2 > 10000000)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}

		if ((num1 > 10000000) || (num2 > 10000000)){
			CHECK_THROWS(mat(num1, num2, '#', '-'));
		}
	}
}

