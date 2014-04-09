#include "DietCommand.h"
#include "CTException.h"

/*
*	DietCommandParam Implementation
*
*/
void DietCommandParam::SetValue(const std::string &value) {
	throw NotYetImplementedException();
}

std::string DietCommandParam::GetValue() const {
	throw NotYetImplementedException();
}

/*
 *	DietCommands Implementation
 *
 */
void DietCommands::AddDietCommand(string &name) {
	commands.insert(make_pair(name, DietCommand(name)));
}