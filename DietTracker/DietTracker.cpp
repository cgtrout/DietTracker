// DietTracker.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include "Test.h"
#include "AllTests.h"

#include "CTString.h"
#include "DietSystem.h"

#ifdef _DEBUG
 extern Tester tester;

 
void TestAll()
{
    AllTests::addSuites();
    tester.RunAllSuites();
}
#endif

using namespace std;
int main( int argc, char* argv[] )
{
 #ifdef _DEBUG
    TestAll();
 #endif

    string templine;
    DietSystem dietSystem;
    dietSystem.BindFunctions();

    //get storage location
    ifstream path_loader{ "./settings/Storage_Location.txt" };
    if( path_loader.good() ) {
        getline( path_loader, dietSystem.filePath );
        path_loader.close();
        //read food define and daily logs
        try {
            dietSystem.ReadFoodDefine();
        } catch( exception& e ) {
            cout << "Problem loading food definition file \n";
            cout << e.what() << "\n";
        }
        try {
            dietSystem.ReadDailyLogs();
        } catch( exception& e ) {
            cout << "Problem loading DailyLog file \n";
            cout << e.what() << "\n";
        }     
        try {
            dietSystem.ReadTotalCalories();
        } catch( exception& e ) {
            cout << "Problem loading DailyCalories file \n";
            cout << e.what() << "\n";
        }
    } else if ( path_loader.bad() ) {
        cout << "Could not load Storage_Location file" << "\n";
    }

    cout << "Compiled: " << __DATE__ << " " << __TIME__ << "\n\n";

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




