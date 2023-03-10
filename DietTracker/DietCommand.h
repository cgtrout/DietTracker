#ifndef DIETCOMMAND_H
#define DIETCOMMAND_H
	
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <memory>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

string GetCurrentTime();

//
class CommandParamBase {
public:
    CommandParamBase() {}
    
    virtual void SetValue( const std::string &value ) = 0;
	virtual std::string GetValue() const = 0;

    std::string name;
};

//quantity
static std::map <char, std::string> unitTypes{ { 's', "Servings" }, { 'g', "Grams" } };

class CommandParamQuantity : public CommandParamBase {
public:
    CommandParamQuantity() : type( 0 ), value( 0.0f ) {}
    CommandParamQuantity( const string &value ): type( 0 ) { SetValue( value ); }
    void SetValue( const std::string &value );
	std::string GetValue() const;
    void SetType( char type );
    char GetType() const;
    const std::string& GetTypeName() const ;

	float GetFloatValue() const { return value; }
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
    std::string GetValue() const;
private:
    date value;
};

//Time
using namespace boost::posix_time;
class CommandParamTime : public CommandParamBase {
public:
    CommandParamTime( const string &value ) { SetValue( value ); }
    void SetValue( const std::string &value );
    std::string GetValue() const;
private:
    ptime value;
};

//string
class CommandParamString : public CommandParamBase {
public:
    CommandParamString( const string &value ) { SetValue( value ); }
    void SetValue( const std::string &value );
    std::string GetValue() const;
private:
    std::string value;
};

//aliases
using Quantity = CommandParamQuantity;
using Time = CommandParamTime;
using Date = CommandParamDate;
using Name = CommandParamString;
using String = CommandParamString;

//represents one DietTracker command
class DietCommand {
public:
	DietCommand(const std::string &name) : name(name){}
	DietCommand() : name() {}
	
    DietCommand( const DietCommand &other ) = delete;
    DietCommand( DietCommand &&other );
	
    std::function<void()> commandFunction;

    const string& GetName() const { return name; }
    
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