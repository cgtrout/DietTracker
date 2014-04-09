#include <exception>
using namespace std;

class NotYetImplementedException : public exception {
	virtual const char* what() const throw( )
	{
		return "Not yet implemented";
	}
};
