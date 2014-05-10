#include "Test_DietSystem.h"
#include "DietSystem.h"

TestSuite suiteDietSystem("Diet System");
extern Tester tester;

using namespace std;
void Test_DietSystem::addTests()
{
    //TODO find way to test this
    suiteDietSystem.AddTest( "Test Execute Line", []()->bool {
        DietSystem d;
        d.BindFunctions();

        //d.ExecuteLine( "Eat testfood 2g" );
        return false;
    });
    suiteDietSystem.AddTest( "Test invalid command", []()->bool {
        DietSystem d;
        d.BindFunctions();
        bool inException = false;
        try {
            d.ExecuteLine( "invalid" );
        } catch( invalid_argument& ) {
            inException = true;
        }
        return inException;
    });
    suiteDietSystem.AddTest( "Test invalid argument", []()->bool {
        DietSystem d;
        d.BindFunctions();
        bool inException = false;
        try {
            //third argument should be quantity
            d.ExecuteLine( "Eat testfood string" );
        } catch( invalid_argument& ) {
            inException = true;
        }
        return inException;
    });
    suiteDietSystem.AddTest( "Test invalid number of arguments", []()->bool {
        DietSystem d;
        d.BindFunctions();
        bool inException = false;
        try {
            d.ExecuteLine( "Eat testfood 1.0 a b" );
        } catch( invalid_argument& ) {
            inException = true;
        }
        return inException;
    });
    suiteDietSystem.AddTest( "Define - test invalid param ", []()->bool {
        DietSystem d;
        d.BindFunctions();

        bool inException = false;
        try {
            d.ExecuteLine( "define food wrong 1.0f" );
        } catch( invalid_argument& ) {
            inException = true;
        }
        return inException;
    });
    suiteDietSystem.AddTest( "Parse recipe string ", []()->bool {
        DietSystem d;
        d.BindFunctions();

        d.ExecuteLine( "define food1 1 1" );
        d.ExecuteLine( "define food2 2 2" );
        d.ExecuteLine( "define recipe { food1=1s, food2=1s }" );

        return d.foodDatabase.database[ 2 ]->GetName() == "recipe";
    });
    suiteDietSystem.AddTest( "Calculate calories", []()->bool {
        DietSystem d;
        d.BindFunctions();

        //define foodname servingsize calories/serving
        d.ExecuteLine( "define food1 1g 100" );
        d.ExecuteLine( "define food2 1.5g 200" );
        d.ExecuteLine( "define r1 { food1=3s, food2=2s }" );
        d.ExecuteLine( "eat r1 1s" );
        
        //calculate calories
        //should calculate to 600
        float calories = d.dailyLog.CalculateCalories();
        return calories == 600;
    });
    tester.AddSuite( suiteDietSystem );
}