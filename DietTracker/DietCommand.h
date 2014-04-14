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

class CommandParamQuantity : public CommandParamBase {
	void SetValue(const std::string &value);
	std::string GetValue();
private:
	float value;
};

//represents one DietTracker command
class DietCommand {
public:
	DietCommand(std::string name) : name(name), params(){};
	
	~DietCommand() {}
	DietCommand(const DietCommand &other) = delete;
	DietCommand(DietCommand &&other);
	
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

}dietCommands;

#endif