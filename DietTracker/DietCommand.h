#ifndef DIETCOMMAND_H
#define DIETCOMMAND_H
	
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;

//
class CommandParamBase {
public:
    CommandParamBase() {}
    
    virtual void SetValue( const std::string &value ) = 0;
	virtual std::string GetValue() = 0;

    std::string name;
};

//quantity
static std::map <char, std::string> unitTypes{ { 's', "Servings" }, { 'g', "Grams" } };

class CommandParamQuantity : public CommandParamBase {
public:
    CommandParamQuantity() : type( 0 ), value( 0.0f ) {}
    CommandParamQuantity( const string &value ): type( 0 ) { SetValue( value ); }
    void SetValue( const std::string &value );
	std::string GetValue();
    void SetType( char type );
    char GetType();
    const std::string& GetTypeName();

	float GetFloatValue() { return value; }
private:
	float value;
    
    char type;
};

using namespace boost::gregorian;

//Date
class CommandParamDate : public CommandParamBase {
public:
    CommandParamDate( const string &value ) { SetValue( value ); }
    void SetValue( const std::string &value );
    std::string GetValue();
private:
    date value;
};

//Time
using namespace boost::posix_time;
class CommandParamTime : public CommandParamBase {
public:
    CommandParamTime( const string &value ) { SetValue( value ); }
    void SetValue( const std::string &value );
    std::string GetValue();
private:
    ptime value;
};

//string
class CommandParamString : public CommandParamBase {
public:
    CommandParamString( const string &value ) { SetValue( value ); }
    void SetValue( const std::string &value );
    std::string GetValue();
private:
    std::string value;
};

//aliases
using Quantity = CommandParamQuantity;
using Time = CommandParamTime;
using Date = CommandParamDate;
using Name = CommandParamString;

//represents one DietTracker command
class DietCommand {
public:
	DietCommand(const std::string &name) : name(name), params(){}
	DietCommand() : name(), params() {}
	~DietCommand() {}
    DietCommand( const DietCommand &other ) = delete;
    DietCommand( DietCommand &&other );

    void AddParam( const string &name, unique_ptr<CommandParamBase> param );
	
    std::function<void()> commandFunction;
    std::vector<unique_ptr<CommandParamBase>> params;
private:
	std::string name;
};

//represents several DietComands
class DietCommands {
public:
    void AddDietCommand( string name );
    bool DoesCommandExist( const string &name );
    size_t GetCommandsCount() { return commands.size(); }

    std::map<std::string, DietCommand> commands;
};

#endif