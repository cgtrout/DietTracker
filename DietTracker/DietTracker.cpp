// DietTracker.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
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

    //get storage location and load food definition file
    string file_path{};
    ifstream path_loader{ "./settings/Storage_Location.txt" };
    if( path_loader.good() ) {
        getline( path_loader, file_path );
        path_loader.close();

        try {
            dietSystem.ExecuteFile( file_path );
        } catch( exception& e ) {
            cout << "Problem loading food definition file \n";
            cout << e.what() << "\n";
        }
    } else if ( path_loader.bad() ) {
        cout << "Could not load food definition file" << "\n";
    }

    while( true ) {
        cout << "DietTracker > ";
        getline( cin, templine );
        if( templine == "quit" ) {
            return 0;
        } else {
            try {
                dietSystem.ExecuteLine( templine );
            } catch( invalid_argument& e) {
                cout << "Invalid:" << e.what() << endl;
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


