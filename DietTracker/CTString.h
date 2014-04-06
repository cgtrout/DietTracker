#ifndef CTSTRING_H
#define CTSTRING_H

#include <vector>
#include <string>

using namespace std;

//split string using delimiter.  Split strings returned in vector
vector<string> split(string &instring, string delim = " ")
{
	vector<string> vec;
	
	size_t pos = 0;
	size_t lastpos = 0;
	while(pos != string::npos) {
		pos = instring.find_first_of(delim, pos);
		char tempDelim = instring[pos];
		while(instring[pos++] == tempDelim);
		
		if(pos != string::npos) {
			vec.push_back(instring.substr(lastpos, pos - lastpos));
		}
		lastpos = pos;
	} 
	return split;
}

#endif //CTSTRING