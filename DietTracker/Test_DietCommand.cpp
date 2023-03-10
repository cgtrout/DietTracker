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
         dc.AddDietCommand( "Test 1" );

         return dc.commands.size() == 1;
     });
     suiteDietCommand.AddTest("Test Diet Command Lambdas", []()-> bool {
         struct CommandFrameWork {
             DietCommands dc;
             int x = 4;
             void a() { x++; }
         }test;
         test.dc.AddDietCommand( "TestA" );
         test.dc.commands[ "TestA" ].commandFunction = [&test]() { test.a(); };
         test.dc.commands[ "TestA" ].commandFunction();
         return test.x == 5;
     });
     suiteDietCommand.AddTest("Test CommandParamQuantity set", []()->bool {
         DietCommands dc;

         Quantity quantity;
         quantity.SetValue( "14.0s" );
         auto value = std::stof( quantity.GetValue() );

         return value == 14.0;
     });
     suiteDietCommand.AddTest("Test Quantity: invalid type ", []()->bool {
         bool inException = false;

         CommandParamQuantity q;
         try {
             q.SetValue( "14.0a" );
         } catch( invalid_argument& ) {
             inException = true;
         }
         return inException;
     } );
     suiteDietCommand.AddTest( "Test Quantity: invalid float value ", []()->bool {
         bool inException = false;

         CommandParamQuantity q;
         try {
             q.SetValue( "a3434b" );
         } catch( invalid_argument& ) {
             inException = true;
         }
         return inException;
     } );
     suiteDietCommand.AddTest( "Test CommandParamQuantity Types", []()->bool {
         CommandParamQuantity q;
         q.SetValue( "12.0" );
         q.SetType( 'g' );
         bool exceptionCaught = false;
         try {
             q.SetType( 'd' );
         } catch( invalid_argument& ) {
             exceptionCaught = true;
         }
         return exceptionCaught;
     } );
     suiteDietCommand.AddTest( "Test CommandParamDate", []()->bool {
         auto testInput = "2002-01-25";
         CommandParamDate param( testInput );
         auto out = param.GetValue();
         return out == testInput;
     } );
     suiteDietCommand.AddTest( "Test CommandParamString", []()->bool {
         auto testInput = "Test1";
         CommandParamString test( testInput );

         return testInput == test.GetValue();
     } );
     suiteDietCommand.AddTest( "Test CommandParamTime set/get", []()->bool {
         auto testInput = "23:59:59";
         CommandParamTime test( testInput );

         auto out = test.GetValue();
         return testInput == out;
     } );
     tester.AddSuite( suiteDietCommand );
}