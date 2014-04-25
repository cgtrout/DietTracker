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

//AddRecipeItem
void Recipe::AddRecipeItem( unique_ptr<RecipeItem> item )
{
    components.push_back( std::move(item) );
}

/*
 *  DietEntry Class
 *   Implemenation
 */
DietEntry::DietEntry( unique_ptr<RecipeItem> iitem, Time itime, Date idate )
    : item( std::move( iitem ) )
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