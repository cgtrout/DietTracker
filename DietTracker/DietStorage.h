#ifndef DIETSTORAGE_H
#define DIETSTORAGE_H

#include <string>
#include <vector>
#include <utility>

//represents one diet system entry
class DietEntry {
    //food
    //Quantity quantity;
    //date
    //time
};

//holds all of the individual DietEntrys
class DailyLogs {
    //list of DietEntries
};

class Recipe {
    //pairs with recipe and serving size
    //TODO this may not be the best way to do this
    //std::vector<std::pair<Recipe, float>> recipeList;
    //std::vector<std::pair<Food, float>> foodList;
};

class Food {
    std::string name;
    float servingSize;
    float caloriesPerServing;
};

#endif //DIETSTORAGE_H