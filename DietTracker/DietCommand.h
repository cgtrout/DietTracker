#ifndef DIETCOMMAND_H
#define DIETCOMMAND_T
	
#include <string>
#include <functional>
#include <vector>
#include <map>

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
	
//private:
	std::string name;
	std::function<void()> commandFunction;
	std::vector<DietCommandParam> params;
};

std::map<std::string, DietCommand> dietCommands;

std::map<std::string, std::string> testMap;
void test() {
	dietCommands["Test"] = { "Test", []() { }, { "test" } };
}


#endif