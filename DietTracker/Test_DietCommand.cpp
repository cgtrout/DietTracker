#include "Test_DietCommand.h"

#include <vector>
#include <string>
#include <iostream>

#include "DietCommand.h"

TestSuite suiteDietCommand("DietCommand");
extern Tester tester;

using namespace std;
void Test_DietCommand::addTests() {
	suiteDietCommand.AddTest("Add Diet Command", []()-> bool {
		DietCommands dc;
		dc.AddDietCommand("Test 1");
		
		return dc.commands.size() == 1;
	});
	suiteDietCommand.AddTest("Test CommandParamQuantity set", []()->bool {
		DietCommands dc;
		dc.AddDietCommand("Test 2");

		//dc.commands["Test 2"].params.push_back(unique_ptr<CommandParamBase>(new CommandParamQuantity()));
		dc.commands["Test 2"].AddParam(new CommandParamQuantity());

		dc.commands["Test 2"].params[0]->SetValue("14.0");

		auto value = std::stof(dc.commands["Test 2"].params[0]->GetValue());

		return value == 14.0;
	});

	tester.AddSuite(suiteDietCommand);
}