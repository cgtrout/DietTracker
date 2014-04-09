#include "DietCommand.h"
#include "CTException.h"

/*
*	DietCommandParam Implementation
*
*/
//Quantity implementation
void CommandParamQuantity::SetValue(const std::string &value) {
	this->value = stof(value);
}

std::string CommandParamQuantity::GetValue() {
	return to_string(value);
}

/*
 *	DietCommands Implementation
 *
 */
void DietCommands::AddDietCommand(string &name) {
	commands.insert(make_pair(name, DietCommand(name)));
}