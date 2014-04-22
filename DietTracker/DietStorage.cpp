#include "DietStorage.h"

/*
 *  Recipe Class
 *   Implemenation
 */

void Recipe::AddRecipeItem( RecipeItem item )
{
    components.push_back( make_unique<RecipeItem>(item) );
}
