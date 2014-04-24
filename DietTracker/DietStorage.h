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

    float GetServingSize() { return servingSize; }
    float GetCaloriesPerServing() { return caloriesPerServing; }

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
    DietEntry( RecipeItem item, Time itime, Date idate );
    
    DietEntry( const DietEntry& ) = delete;
    DietEntry( DietEntry&& );

    unique_ptr<RecipeItem> item;
    string mtime;
    string mdate;
};

//holds all of the individual DietEntrys
class DailyLog {
public:
    void AddEntry( DietEntry entry );
    
    //list of DietEntries
    std::vector<unique_ptr<DietEntry>> entries;
};

#endif //DIETSTORAGE_H