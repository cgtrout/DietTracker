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

//DateTime implementation
void CommandParamDateTime::SetValue( const std::string &value )
{
    this->value = date( from_string(value) );
}

std::string CommandParamDateTime::GetValue()
{
    return to_iso_extended_string( value );
}

//string implementation
void CommandParamString::SetValue( const std::string &value )
{
    this->value = value;
}

std::string CommandParamString::GetValue()
{
    return value;
}

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

void DietCommand::AddParam(CommandParamBase *param) {
	params.push_back(unique_ptr<CommandParamBase>(param));
}

void DietCommands::AddDietCommand(string name) {
	commands.insert(make_pair(name, DietCommand(name)));
}
