#include "Test_DietStorage.h"

//#include <vector>
//#include <string>
#include <iostream>

#include "DietStorage.h"

TestSuite suiteDietStorage( "DietStorage" );
extern Tester tester;

using namespace std;
void Test_DietStorage::addTests()
{
    suiteDietStorage.AddTest( "Create a recipe", []()->bool {
        auto recipe = make_unique<Recipe>( "main recipe" );

        auto food = make_unique<Food>( "Food" );
        food->quantity.SetValue( "5.0s" );

        recipe->AddRecipeItem( std::move( food ) );

        auto internal_recipe = make_unique<Recipe>( "internal recipe" );
        auto food2 = make_unique<Food>( "FoodInternal", Quantity( "1.0s" ), 2.0f, 3.0f );
        internal_recipe->AddRecipeItem( std::move( food2 ) );
        recipe->AddRecipeItem( std::move( internal_recipe ) );
        
        auto testrecipe = dynamic_cast<Recipe*>( recipe->components[1].get() );
        auto testfood = dynamic_cast<Food*>( testrecipe->components[0].get() );
        return testfood->GetServingSize() == 2.0f;
    });

    suiteDietStorage.AddTest( "DailyLogs test", []()->bool {
        DailyLog log;
        auto food = make_unique<Food>( "food" );
        
        log.AddEntry( DietEntry( std::move(food), Time( "07:32" ), Date( "2014-Apr-01" ) ) );
        return log.entries[0]->item->GetName() == "food";
    });

    tester.AddSuite( suiteDietStorage );
}