#include "Test_CTString.h"
#include "CTString.h"

#include <vector>
#include <string>
#include <iostream>

TestSuite suite("CTString");
extern Tester tester;

using namespace std;
void Test_CTString::addTests() {
	suite.AddTest("Test Split / multiple spaces", []()-> bool {
		string test = "This  is a test";

		vector<string> stringvector = split(test);

		return ( stringvector[0] == "This" && stringvector[3] == "test" );
	});
	suite.AddTest("Test no delimeters", []()-> bool {
		string test = "Superlongword";

		vector<string> stringvector = split(test);

		return ( stringvector[0] == "Superlongword" );
	});

	tester.AddSuite(suite);
}