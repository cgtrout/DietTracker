// DietTracker.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[])
{
	string templine;
	cout << "DietTracker > ";
	cin >> templine;
	cout << "Executing: " << templine << endl;

	cout << "Hit enter to close";
	
	cin >> templine;
	return 0;
}


