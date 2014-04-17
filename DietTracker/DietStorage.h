#ifndef DIETSTORAGE_H
#define DIETSTORAGE_H

#include <string>
#include <vector>

//base class for recipes and foods
class RecipeBase {

};

class RecipeItem;

class Recipe : public RecipeBase {
    std::vector<RecipeItem> items;
};

class RecipeItem {
    RecipeBase recipe;
    float servingSize;
};

class Food : public RecipeBase {
    std::string name;
    float servingSize;
    float caloriesPerServing;
};

#endif //DIETSTORAGE_H