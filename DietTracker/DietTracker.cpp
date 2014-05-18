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

    //get storage location
    string file_path{};
    ifstream path_loader{ "./settings/Storage_Location.txt" };
    if( path_loader.good() ) {
        getline( path_loader, file_path );
        path_loader.close();
        
        try {
            //load FoodDefines
            dietSystem.ExecuteFile( file_path + "FoodDefines.txt" );
        } catch( exception& e ) {
            cout << "Problem loading food definition file \n";
            cout << e.what() << "\n";
        }
        try {
            //load DailyLog
            dietSystem.ExecuteFile( file_path + "DailyLog.txt" );
        } catch( exception& e ) {
            cout << "Problem loading DailyLog file \n";
            cout << e.what() << "\n";
        }       
    } else if ( path_loader.bad() ) {
        cout << "Could not load Storage_Location file" << "\n";
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


