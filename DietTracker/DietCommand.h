#ifndef DIETCOMMAND_H
#define DIETCOMMAND_H
	
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <memory>

using namespace std;

//
class CommandParamBase {
public:
	virtual void SetValue(const std::string &value) = 0;
	virtual std::string GetValue() = 0;

};

//quantity
class CommandParamQuantity : public CommandParamBase {
	void SetValue(const std::string &value);
	std::string GetValue();

	float GetFloatValue() { return value; }
private:
	float value;
};

//TODO DateTime
class CommandParamDateTime : public CommandParamBase {
    void SetValue( const std::string &value );
    std::string GetValue();
};

//represents one DietTracker command
class DietCommand {
public:
	DietCommand(const std::string &name) : name(name), params(){}
	DietCommand() : name(), params() {}
	~DietCommand() {}
	DietCommand(const DietCommand &other) = delete;
	DietCommand(DietCommand &&other);

	void AddParam(CommandParamBase *param);
	
	std::function<void()> commandFunction;
	std::vector<unique_ptr<CommandParamBase>> params;
private:
	std::string name;
};

//represents several DietComands
class DietCommands {
public:
	void AddDietCommand(string name);

	std::map<std::string, DietCommand> commands;

};

#endif