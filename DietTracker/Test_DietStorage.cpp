#include "Test_DietStorage.h"

//#include <vector>
//#include <string>
#include <iostream>

#include "DietStorage.h"

TestSuite suiteDietStorage( "DietStorage" );
extern Tester tester;

using namespace std;
void Test_DietStorage::addTests()
{
    //TODO add tests here
    tester.AddSuite( suiteDietStorage );
}