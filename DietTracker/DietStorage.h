#ifndef DIETSTORAGE_H
#define DIETSTORAGE_H

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "DietCommand.h"

using namespace std;

using namespace boost::gregorian;
using namespace boost::posix_time;

using Quantity = CommandParamQuantity;

//base class for Recipe/Food
class RecipeItem {
public:
    Quantity quantity;

    const string& GetName() { return name; }
protected:
    RecipeItem( const string &name, Quantity quantity ) : name( name ), quantity( quantity ) {}
    std::string name;
};

class Food : public RecipeItem {
public:
    Food( const string &name, Quantity quantity, float servingSize, float caloriesPerServing );
    Food( const string &name );
private:
    float servingSize;
    float caloriesPerServing;
};

class Recipe : public RecipeItem {
public:
    Recipe( const string &name );
    Recipe( const string &name, Quantity quantity );
    
    void AddRecipeItem( RecipeItem item  );
    
    std::vector<unique_ptr<RecipeItem>> components;
private:

};

//represents one diet system entry
class DietEntry {
public:
    unique_ptr<RecipeItem> food;
    ptime time;
    date mdate;
};

//holds all of the individual DietEntrys
class DailyLogs {
    //list of DietEntries
};

#endif //DIETSTORAGE_H