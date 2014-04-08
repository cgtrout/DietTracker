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
	//enum class type { string, quantity, dateTime, recipe };
	//bool validate();
//private:
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

std::map<std::string, DietCommand> dietCommands;

void AddDietCommand(string name);

#endif