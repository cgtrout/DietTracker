#include "DietCommand.h"
#include "CTException.h"
#include <locale>
/*
*	DietCommandParam Implementation
*
*/

//Quantity implementation
void CommandParamQuantity::SetValue(const std::string &value) {
    char lastChar = value[ value.length() - 1 ];
    int lastIsChar = isalpha( lastChar );
    if( lastIsChar ) {
        //is the last char a valid type?
        if( unitTypes.count( lastChar ) == 0 ) {
            throw invalid_argument( "Invalid quantity type" );
        }
        this->value = stof(value.substr( 0, value.length() - 1 ));
    } else {
        //default is s (serving) if not specified
        type = 's';
        this->value = stof( value );
    }
}

std::string CommandParamQuantity::GetValue() {
    if( type > 0 ) {
        return to_string( value );
    } else {
        return to_string( value ) + type;
    }
}

void CommandParamQuantity::SetType( char type ) {
    //ensure type given exists
    if( unitTypes.count( type ) == 0 ) {
        throw invalid_argument( "CommandParamQuantity: invalid type" );
    }

    this->type = type;
}

char CommandParamQuantity::GetType() {
    return type;
}

const std::string& CommandParamQuantity::GetTypeName() {
    return unitTypes[ type ];
}

//Date implementation
void CommandParamDate::SetValue( const std::string &value )
{
    this->value = date( from_string(value) );   
}

std::string CommandParamDate::GetValue()
{
    return to_iso_extended_string( value );
}

//Time implementation
void CommandParamTime::SetValue( const std::string &value ) {
    //add dummy date (we want to just deal with the time)
    this->value = time_from_string( "2000-01-01 "+ value );
}

std::string CommandParamTime::GetValue() {
    string sval = to_simple_string( value );
    auto pos = sval.find_first_of( " " );
    pos++;
    return sval.substr( pos );
}
//string implementation
void CommandParamString::SetValue( const std::string &value ) {
    this->value = value;
}

std::string CommandParamString::GetValue() {
    return value;
}

/*
 *	DietCommand Implementation
 *
 */

//move constructor
DietCommand::DietCommand(DietCommand &&other) 
  :	params(std::move(other.params)), 
	commandFunction(std::move(other.commandFunction)), 
	name(std::move(other.name)) {
}

void DietCommand::AddParam( unique_ptr<CommandParamBase> param ) {
    params.push_back( std::move( param ) );
}

/*
*	DietCommands Implementation
*
*/
void DietCommands::AddDietCommand(string name) {
	commands.insert(make_pair(name, DietCommand(name)));
}
