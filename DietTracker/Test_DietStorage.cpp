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
        Recipe recipe;

        Food food;
        food.name = "Food";
        food.quantity.SetValue( "5.0s" );

        recipe.AddRecipeItem( food );

        Recipe internal_recipe;
        Food food2;
        food2.name = "FoodInternal";
        
        internal_recipe.name = "internal recipe";
        internal_recipe.AddRecipeItem( food2 );

        recipe.AddRecipeItem( internal_recipe );     

        return recipe.components[1]->name == "internal recipe"; //it compiles, were happy
    });

    tester.AddSuite( suiteDietStorage );
}