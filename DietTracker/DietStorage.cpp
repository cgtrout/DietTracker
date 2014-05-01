#include "DietStorage.h"

/*
 *  Food Class
 *   Implemenation
 */

//constructor
Food::Food( const std::string &iname, Quantity iquantity, float iservingSize, float icaloriesPerServing )
    : RecipeItem( iname, iquantity)
    , servingSize( iservingSize )
    , caloriesPerServing( icaloriesPerServing )
{}

Food::Food( const string &name) 
    : RecipeItem( name, Quantity("0.0s"))
    , servingSize ( 0.0f )
    , caloriesPerServing ( 0.0f )
{}

/*
 *  Recipe Class
 *   Implemenation
 */

//constructors
Recipe::Recipe( const string &iname )
    : RecipeItem(iname, Quantity("1.0"))
{}

Recipe::Recipe( const string &name, Quantity quantity )
    : RecipeItem( name, quantity )
{}

//AddRecipeComponent
void Recipe::AddRecipeComponent( RecipeItem *item, Quantity quant )
{
    components.push_back( make_unique<RecipeComponent>( item, quant ) );
}

/*
 *  DietEntry Class
 *   Implemenation
 */
DietEntry::DietEntry( RecipeItem *iitem, Quantity quant, Time itime, Date idate )
    : quantity( quant )
    , item( iitem )
    , mtime( itime.GetValue() )
    , mdate( idate.GetValue() )
{}

DietEntry::DietEntry( DietEntry &&entry )
    : item( std::move( entry.item ) )
    , mtime( std::move(entry.mtime ) )
    , mdate( std::move(entry.mdate ) )
{}

/*
 *  DailyLogs Class
 *   Implemenation
 */
void DailyLog::AddEntry( DietEntry entry )
{
    entries.push_back( make_unique<DietEntry>( std::move( entry ) ) );
}

/*
 *  DailyLogs Class
 *   Implemenation
 */
void FoodDatabase::AddFood( unique_ptr<RecipeItem> item )
{
    database.push_back( std::move( item ) );
}