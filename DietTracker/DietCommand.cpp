#include "DietCommand.h"
#include "CTException.h"
#include <locale>

//GetCurrentTime implementation
string GetCurrentTime()
{
    ptime t(second_clock::local_time());
    auto timestring = to_simple_string( t );
    auto spacepos = timestring.find_first_of( " " );
    spacepos++;
    auto out = timestring.substr( spacepos );
    return out;
}

/*
*	DietCommandParam Implementation
*
*/

//Quantity implementation
void CommandParamQuantity::SetValue(const std::string &value) {
    char lastChar = value[ value.length() - 1 ];
    int lastIsChar_bool = isalpha( lastChar );
    if( lastIsChar_bool ) {
        //is the last char a valid type?
        if( unitTypes.count( lastChar ) == 0 ) {
            throw invalid_argument( "Invalid quantity type" );
        }
        this->value = stof(value.substr( 0, value.length() - 1 ));
        this->type = lastChar;
    } else {
        //default is s (serving) if not specified
        type = 's';
        this->value = stof( value );
    }
}

std::string CommandParamQuantity::GetValue() const {
    if( type == 0 ) {
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

char CommandParamQuantity::GetType() const {
    return type;
}

const std::string& CommandParamQuantity::GetTypeName() const {
    return unitTypes[ type ];
}

//Date implementation
void CommandParamDate::SetValue( const std::string &value )
{
    this->value = date( from_string(value) );   
}

std::string CommandParamDate::GetValue() const
{
    return to_iso_extended_string( value );
}

//Time implementation
void CommandParamTime::SetValue( const std::string &value ) {
    //add dummy date (we want to just deal with the time)
    this->value = time_from_string( "2000-01-01 "+ value );
}

std::string CommandParamTime::GetValue() const {
    string sval = to_simple_string( value );
    auto pos = sval.find_first_of( " " );
    pos++;
    return sval.substr( pos );
}
//string implementation
void CommandParamString::SetValue( const std::string &value ) {
    this->value = value;
}

std::string CommandParamString::GetValue() const {
    return value;
}

/*
 *	DietCommand Implementation
 *
 */

//move constructor
DietCommand::DietCommand(DietCommand &&other) 
  :	commandFunction(std::move(other.commandFunction))
  ,	name(std::move(other.name)) {
}


/*
*	DietCommands Implementation
*
*/
void DietCommands::AddDietCommand(string name) {
	commands.insert(make_pair(name, DietCommand(name)));
}

bool DietCommands::DoesCommandExist( const string &name )
{
    return commands.count( name ) > 0;
}
