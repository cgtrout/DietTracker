#include "Test_DietSystem.h"
#include "DietSystem.h"

TestSuite suiteDietSystem("Diet System");
extern Tester tester;

using namespace std;
void Test_DietSystem::addTests()
{
    suiteDietSystem.AddTest( "Test binded function: eat", []()->bool {
        DietSystem d;
        d.BindFunctions();

        auto v = stof(d.dietCommands.commands[ "Eat" ].params[ 0 ]->GetValue());
        return v == 0.0f;
    });
    suiteDietSystem.AddTest( "Test Execute Line", []()->bool {
        DietSystem d;
        d.BindFunctions();

        d.ExecuteLine( "Eat testfood 2g" );
        return false;
    });
    tester.AddSuite( suiteDietSystem );
}