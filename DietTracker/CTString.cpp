#include "CTString.h"

//split string using delimiter.  Split strings returned in vector
vector<string> split(string &instring, string delim)
{
	vector<string> vec;

	size_t pos = 0;
	size_t lastpos = 0;
	size_t length = 0;
	while(pos != string::npos) {
		pos = instring.find_first_of(delim, pos);

		if(pos != string::npos) {
			char tempDelim = instring[pos++];
			length = pos - lastpos - 1;
			while(instring[pos] == tempDelim) {
				pos++;
			}
			vec.push_back(instring.substr(lastpos, length));
		} else {
			vec.push_back(instring.substr(lastpos, instring.length() - lastpos));
		}
		lastpos = pos;
	}
	return vec;
}