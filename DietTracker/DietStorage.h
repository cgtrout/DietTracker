#ifndef DIETSTORAGE_H
#define DIETSTORAGE_H

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "DietCommand.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

//base class for Recipe/Food
class RecipeItem {
    std::string name;
    Quantity quantity;
};

class Food : public RecipeItem {
    float servingSize;
    float caloriesPerServing;
};

class Recipe : public RecipeItem {
    std::vector<unique_ptr<RecipeItem>> components;
};

using Quantity = CommandParamQuantity;

//represents one diet system entry
class DietEntry {
    unique_ptr<RecipeItem> food;
    ptime time;
    date mdate;
};

//holds all of the individual DietEntrys
class DailyLogs {
    //list of DietEntries
};



#endif //DIETSTORAGE_H