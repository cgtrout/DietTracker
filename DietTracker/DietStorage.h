#ifndef DIETSTORAGE_H
#define DIETSTORAGE_H

#include <string>
#include <vector>
#include <utility>

class Recipe {
    //pairs with recipe and serving size
    //TODO this may not be the best way to do this
    std::vector<std::pair<Recipe, float>> recipeList;
    std::vector<std::pair<Food, float>> foodList;
};

class RecipeItem {
    RecipeBase recipe;
    float servingSize;
};

class Food {
    std::string name;
    float servingSize;
    float caloriesPerServing;
};

#endif //DIETSTORAGE_H