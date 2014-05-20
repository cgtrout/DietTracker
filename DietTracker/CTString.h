#ifndef CTSTRING_H
#define CTSTRING_H

#include <vector>
#include <string>

using namespace std;

//split string using delimiter.  Split strings returned in vector
vector<string> split(const string &instring, string delim = " ");

//Parse command line for recipe program
vector<string> parseCommandLine(const string &instring);

#endif //CTSTRING