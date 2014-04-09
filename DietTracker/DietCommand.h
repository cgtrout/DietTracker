#ifndef DIETCOMMAND_H
#define DIETCOMMAND_H
	
#include <string>
#include <functional>
#include <vector>
#include <map>

using namespace std;

//Specification of one command param
class DietCommandParam {
public:
	enum class param_type { string, quantity, dateTime, recipe }type;
	void SetValue(std::string value);
	std::string GetValue() const;
private:
	std::string value;
};

//represents one DietTracker command
class DietCommand {
public:
	DietCommand(std::string name) : name(name){};

	std::function<void()> commandFunction;
	std::vector<DietCommandParam> params;
private:
	std::string name;
};

//represents several DietComands
class DietCommands {
public:
	void AddDietCommand(string &name);

	std::map<std::string, DietCommand> commands;
}dietCommands;

#endif