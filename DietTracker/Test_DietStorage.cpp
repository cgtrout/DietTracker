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
        Recipe recipe( "main recipe" );

        Food food( "Food" );
        food.quantity.SetValue( "5.0s" );

        recipe.AddRecipeItem( food );

        Recipe internal_recipe( "internal recipe" );
        Food food2( "FoodInternal" );

        internal_recipe.AddRecipeItem( food2 );

        recipe.AddRecipeItem( internal_recipe );     

        return recipe.components[1]->GetName() == "internal recipe"; 
    });

    tester.AddSuite( suiteDietStorage );
}