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
    RecipeItem( const RecipeItem& ) = delete;

    virtual const string& GetName() { return name; }
    virtual string ToString() { return name; }
protected:
    RecipeItem( const string &name ) : name( name ) {}
    
    std::string name;
};

class Food : public RecipeItem {
public:
    Food( const string &name, float servingSize, float caloriesPerServing );
    Food( const string &name );
    Food( const Food& ) = delete;

    float GetServingSize() { return servingSize; }
    float GetCaloriesPerServing() { return caloriesPerServing; }
    virtual string ToString() { return "Food: " + name; }
private:
    float servingSize;
    float caloriesPerServing;
};

class RecipeComponent {
public:
    RecipeComponent( RecipeItem *i, Quantity q ) : item( i ), quantity( q ) {}
    RecipeComponent() = delete;

    RecipeItem *item;
    Quantity quantity;
};

class Recipe : public RecipeItem {
public:
    Recipe( const string &name );
    //Recipe( const string &name, Quantity quantity );
    Recipe( const Recipe& ) = delete;
    virtual string ToString() { return "Recipe: " + name; }
    
    void AddRecipeComponent( RecipeItem *item, Quantity quant );
    
    std::vector<unique_ptr<RecipeComponent>> components;
private:

};

//represents one diet system entry
class DietEntry {
public:
    DietEntry( RecipeItem *iitem, Quantity quantity, Time itime, Date idate );
    
    DietEntry( const DietEntry& ) = delete;
    DietEntry( DietEntry&& );

    RecipeItem *item;
    Quantity quantity;
    
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

class FoodDatabase {
public:
    void AddFood( unique_ptr<RecipeItem> item );
    
    //parse recipe from string
    void AddRecipe( const string &name, const string &recipe );

    void PrintAll();
    
    std::vector<unique_ptr<RecipeItem>> database;

private:
    //this class handles parsing of recipe strings
    class RecipeParser {
     public:
        RecipeParser( const string &s ) : workString( s ) {}
        void SkipWhiteSpace();
        string ReadToken( const string &delim );
        void ExpectSymbol( char s );
        char Peek();
        bool End() { return pos == workString.length(); }
     private:
        size_t pos = 0;
        string workString;
    };
};

#endif //DIETSTORAGE_H