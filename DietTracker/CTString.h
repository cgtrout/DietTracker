#ifndef CTSTRING_H
#define CTSTRING_H

#include <vector>
#include <string>

using namespace std;

//split string using delimiter.  Split strings returned in vector
vector<string> split(string &instring, string delim = " ");

//Parse command line for recipe program
//TODO this should be moved when it is apparent where it belongs
vector<string> parseCommandLine(string &instring);

#endif //CTSTRING