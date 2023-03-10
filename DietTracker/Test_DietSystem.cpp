#include "Test_DietSystem.h"
#include "DietSystem.h"

TestSuite suiteDietSystem("Diet System");
extern Tester tester;

using namespace std;
void Test_DietSystem::addTests()
{
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
        //should calculate to 700
        float calories = d.dailyLog.CalculateCalories();
        return calories == 700;
    });
    suiteDietSystem.AddTest( "Calculate calories of recipe using grams", []()->bool {
        DietSystem d;
        d.BindFunctions();

        //define foodname servingsize calories/serving
        d.ExecuteLine( "define food1 1g 100" ); //3g
        d.ExecuteLine( "define food2 1.5g 150" );//3g
        d.ExecuteLine( "define r1 { food1=3g, food2=2s }" );
        d.ExecuteLine( "eat r1 1g" );
        
        //calculate calories
        float calories = d.dailyLog.CalculateCalories();
        return calories == 100;
    });
    suiteDietSystem.AddTest( "Test load from file", []()->bool {
        DietSystem d;
        d.BindFunctions();

        d.ExecuteFile( "./storage/_test.food" );
        d.ExecuteLine( "eat chili_meal 1s" );
        float calories = d.dailyLog.CalculateCalories();
        return calories == 1247.81372f;
    });
    suiteDietSystem.AddTest( "Test sub command", []()->bool {
        DietSystem d;
        d.BindFunctions();

        d.ExecuteLine( "define food1 100g 100" );
        d.ExecuteLine( "eat food1 100g" );
        d.ExecuteLine( "sub 50g" );

        float cals = d.dailyLog.CalculateCalories();
        return cals == 50;

    });
    suiteDietSystem.AddTest( "Test calc", []()->bool {
        Food f1{ "f1", 100, 450 };
        Food f2{ "f2", 200, 100 };

        Recipe r1{ "r1" };
        r1.AddRecipeComponent( &f1, Quantity("2.0s") );
        r1.AddRecipeComponent( &f2, Quantity( "1.0s" ) );

        float grams = r1.CalculateGrams( 1000 );

        return grams == 400;

    });
    tester.AddSuite( suiteDietSystem );
}