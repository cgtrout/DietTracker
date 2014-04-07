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


vector<string> parseCommandLine(string &instring) {
	size_t pos = 0;
	size_t lastPos = 0;

	vector<string> vec;

	//iterate over string
	for(; pos <= instring.length();) {
		//if at end of string
		if(pos == instring.length()) {
			vec.push_back(instring.substr(lastPos, pos - lastPos));
			break;
		}
		//if at a space
		if(instring[pos] == ' ') {
			//create substring
			vec.push_back(instring.substr(lastPos, pos - lastPos));

			//skip foward until not a space
			for(; instring[pos] == ' ' && pos < instring.length();) {
				pos++;
			}
			lastPos = pos;
		}
		//else if at a start bracket
		else if(instring[pos] == '{') {
			//skip until we find next bracket
			for(; pos < instring.length(); ++pos) {
				if(instring[pos] == '}') {
					break;
				}
			}
			if(instring[pos] == '}') {
				//create substring
				vec.push_back(instring.substr(lastPos, pos - lastPos));
				
				lastPos = pos;
			} else {
				//bracket not found - return error
				throw exception("Bracket missing");
			}
		}
		pos++;
	}

	return vec;
}
