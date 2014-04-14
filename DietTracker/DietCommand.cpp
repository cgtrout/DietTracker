#include "DietCommand.h"
#include "CTException.h"

/*
*	DietCommandParam Implementation
*
*/
//Quantity implementation
//void CommandParamQuantity::SetValue(const std::string &value) {
//	this->value = stof(value);
//}

//std::string CommandParamQuantity::GetValue() {
//	return to_string(value);
//}

/*
 *	DietCommands Implementation
 *
 */

//move constructor
DietCommand::DietCommand(DietCommand &&other) 
  :	params(std::move(other.params)), 
	commandFunction(std::move(other.commandFunction)), 
	name(std::move(other.name)) {
}

void DietCommands::AddDietCommand(string name) {
	commands.insert(make_pair(name, std::move(DietCommand(name))));
}
