// DietTracker.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "Test.h"
#include "AllTests.h"

#include "CTString.h"
#include "DietSystem.h"

extern Tester tester;

void TestAll();

using namespace std;
int main( int argc, char* argv[] )
{
    TestAll();

    string templine;
    DietSystem dietSystem;
    dietSystem.BindFunctions();
    
    while( true ) {
        cout << "DietTracker > ";
        getline( cin, templine );
        if( templine == "quit" ) {
            return 0;
        } else {
            try {
                dietSystem.ExecuteLine( templine );
            } catch( invalid_argument& ) {
                cout << "Invalid command" << endl;
            }
        }
    }
    return 0;
}

void TestAll()
{
    AllTests::addSuites();
    tester.RunAllSuites();
}


