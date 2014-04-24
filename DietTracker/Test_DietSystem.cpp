#include "Test_DietSystem.h"
#include "DietSystem.h"

TestSuite suiteDietSystem("Diet System");
extern Tester tester;

using namespace std;
void Test_DietSystem::addTests()
{
    //TODO Add tests here
    suiteDietSystem.AddTest( "Test binded function: eat", []()->bool {
        DietSystem d;
        d.BindFunctions();

        return true;
    });
    tester.AddSuite( suiteDietSystem );
}