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
        
        recipe->AddRecipeComponent( food.get(), Quantity("1.0s") );

        auto internal_recipe = make_unique<Recipe>( "internal recipe" );
        auto food2 = make_unique<Food>( "FoodInternal", 2.0f, 3.0f );
        internal_recipe->AddRecipeComponent( food2.get(), Quantity( "1.0s" ) );
        recipe->AddRecipeComponent( internal_recipe.get(), Quantity( "1.0s" ) );
        
        auto testrecipe = dynamic_cast<Recipe*>( recipe->components[1]->item );
        auto testfood = dynamic_cast<Food*>( testrecipe->components[0]->item );
        return testfood->GetServingSize() == 2.0f;
    });

    suiteDietStorage.AddTest( "DailyLogs test", []()->bool {
        DailyLog log;
        auto food = make_unique<Food>( "food" );
        
        log.AddEntry( make_unique<DietEntry>( food.get(), Quantity("1.0s"), Time( "07:32" )));
        return log.entries[0]->item->GetName() == "food";
    });

    tester.AddSuite( suiteDietStorage );
}