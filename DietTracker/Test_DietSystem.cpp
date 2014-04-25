#include "Test_DietSystem.h"
#include "DietSystem.h"

TestSuite suiteDietSystem("Diet System");
extern Tester tester;

using namespace std;
void Test_DietSystem::addTests()
{
    suiteDietSystem.AddTest( "Test Execute Line", []()->bool {
        DietSystem d;
        d.BindFunctions();

        d.ExecuteLine( "Eat testfood 2g" );
        return d.dietCommands.commands["eat"].params[0]->GetValue() == "testfood";
    });
    tester.AddSuite( suiteDietSystem );
}