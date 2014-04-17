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

        DietCommand &command = dc.commands[ "Test 2" ];
		command.AddParam(new CommandParamQuantity());
		command.params[0]->SetValue("14.0s");
		auto value = std::stof(command.params[0]->GetValue());

		return value == 14.0;
	});
    suiteDietCommand.AddTest( "Test Quantity: invalid type ", []()->bool {
        bool inException = false;

        CommandParamQuantity q;
        try {
            q.SetValue( "14.0a" );
        } catch( invalid_argument ) {
            inException = true;
        }
        return inException;
    });
    suiteDietCommand.AddTest( "Test CommandParamQuantity Types", []()->bool {
        CommandParamQuantity q;
        q.SetValue( "12.0" );
        q.SetType( 'g' );
        bool exceptionCaught = false;
        try {
            q.SetType( 'd' );
        } catch( invalid_argument ) {
            exceptionCaught = true;
        }
        return exceptionCaught;
    });
    suiteDietCommand.AddTest( "Test CommandParamDateTime", []()->bool {
        CommandParamDateTime param;
        auto testInput = "2002-01-25";
        param.SetValue( testInput );
        auto out = param.GetValue();
        return out == testInput;
    });
    suiteDietCommand.AddTest( "Test CommandParamString", []()->bool {
        auto testInput = "Test1";
        CommandParamString test;
        test.SetValue( testInput );
        return testInput == test.GetValue();
    });
	tester.AddSuite(suiteDietCommand);
}