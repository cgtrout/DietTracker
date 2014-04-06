#ifndef CGT_TEST_H_
#define CGT_TEST_H_

#include <vector>
#include <functional>
#include <chrono>

using namespace std;

//represents one unit test
class Test {
 public:
	Test( const string& name, std::function<bool( )> function );

	//should return true if test was successfull
	bool Run();
	
	const chrono::milliseconds& GetRunTime() const;
	
	const string& GetName() const;
 private:
	std::function<bool()> function;
	string name;
	chrono::milliseconds runTime;
};

//Represents a collection of tests
//Responsible for running all tests
class TestSuite {
 public:
	 TestSuite(string nameOfSuite);

	 void AddTest(const Test& test);
	 void AddTest(const string& name, std::function<bool()> function);
	 
	 //return true if all tests passed
	 bool RunTests();

 private:
	 std::vector<Test> tests;
	 string name;				//name of suite
};

//Holds a collection of TestSuites
//Responsible for running all test suites
class Tester {
 public:
	Tester();
	
	//NOT responsible for mananagement of pointer
	//pass in a ref to an existing stack object
	void AddSuite(TestSuite& suite);
	
	//return true if all suites passed
	bool RunAllSuites();

 private:
	std::vector<TestSuite*> testSuites;
};


#endif CGT_TEST_H_