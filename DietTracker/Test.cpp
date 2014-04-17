#include <iostream>
#include <string>
#include "Test.h"

/*	Class Test
 *	Implementation
 *
 *
 *
 */

//constructor
Test::Test( const string& name, std::function<bool()> func ) :
	function(func),
	name(name),
	runTime(0)
{}

bool Test::Run() {
	//start timer
	using namespace chrono;
	using time_point = high_resolution_clock::time_point;
	time_point start = high_resolution_clock::now();
	
	//run test function
	bool result = function();

	//set time it took to run
	runTime = duration_cast< milliseconds >( high_resolution_clock::now() - start );
	
	return result;
}

inline const chrono::milliseconds& Test::GetRunTime() const {
	return runTime;
}

const string& Test::GetName() const {
	return name;
}

/*	Class TestSuite
*	Implementation
*
*
*
*/

//Constructor
TestSuite::TestSuite(string nameOfSuite) :
	tests(),
	name(nameOfSuite)
{}

//AddTest
void TestSuite::AddTest( const Test& test ) 
{
	tests.push_back( test );
}

void TestSuite::AddTest(const string& name, std::function<bool()> function)
{
	tests.push_back(Test(name, function));
}

//RunTests
bool TestSuite::RunTests()
{
	int failedCount = 0;

	bool allPassed = false;

	cout << "Running Test Suite: " << name << endl;
	cout << "**************************************";
	cout << endl << endl;

	for ( auto &test : tests ) {
		cout << "Running test: " << test.GetName() << endl;
		if(test.Run() == false) {
			cout << "***** Test failed *****" << endl << endl;
			failedCount++;
		} else {
			cout << "Test passed.";
		}
		auto runTime = test.GetRunTime().count();
		if(runTime > 0) {
			cout << "Runtime was " << runTime << "ms";
		}
		cout << endl << endl;
	}

	if(failedCount == 0) {
		cout << endl << "All tests passed." << endl;
		allPassed = true;
	} else {
		cout << endl << failedCount << " Tests have failed" << endl;
		allPassed = false;
	} 

	cout << endl << endl;
	return allPassed;
}

/*
 *	Tester implementation
 *
 *
 */

//constructor
Tester::Tester() {

}

void Tester::AddSuite(TestSuite& suite) {
	testSuites.push_back(&suite);
}

bool Tester::RunAllSuites() {
	bool allPassed = true;

	cout << endl << endl;

	for(auto &suite : testSuites) {
		bool success = suite->RunTests();
		if(!success) {
			allPassed = false;
		}
	}

	if(allPassed) {
		cout << "ALL TEST-SUITES PASSED";
	} else {
		cout << "******************************************************" << endl;
		cout << "******** FAIL - ONE OR MORE TEST HAS FAILED **********";
	}
	cout << endl;

	return allPassed;
}
