#include "DietStorage.h"

/*
 *  Food Class
 *   Implemenation
 */

//constructor
Food::Food( const std::string &iname, float iservingSize, float icaloriesPerServing )
    : RecipeItem( iname )
    , servingSize( iservingSize )
    , caloriesPerServing( icaloriesPerServing )
{}

Food::Food( const string &name) 
    : RecipeItem( name )
    , servingSize ( 0.0f )
    , caloriesPerServing ( 0.0f )
{}

/*
 *  Recipe Class
 *   Implemenation
 */

//constructors
Recipe::Recipe( const string &iname )
    : RecipeItem( iname )
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

void FoodDatabase::AddRecipe( const string &name, const string &recipe )
{
    if( recipe[ 0 ] != '{' || recipe[ recipe.size() - 1 ] != '}' ) {
        throw invalid_argument( "Invalid recipe: must start and end with brackets { }" );
    }

    auto recipe_item = make_unique<Recipe>( name );

    //parse string
    RecipeParser parser{ recipe };

    while( true ) {
        //recipe must start with '{'
        if( parser.ExpectSymbol( '{' ) == false ) {
            throw invalid_argument( "Expected '{'" );
        }
        parser.SkipWhiteSpace();
        
        //read name token
        auto token_name = parser.ReadToken( "= " );
        
        //TODO validate that food item exists in database

        parser.SkipWhiteSpace();
        
        //if a ',' expect more food items, else if a '}' we are done
        auto c = parser.Peek();
        if( c == ',' ) {
            parser.ExpectSymbol( ',' ); //this skips comma
        } else if( c == '}' ) {
            break;
        } else {
            throw invalid_argument( "Expected ',' or '}'" );
        }
    }
}

void FoodDatabase::PrintAll()
{
    for( auto &i : database ) {
        cout << i->ToString() << "\n";
    }
}

/* 
 *  Class RecipeParser
 *
 */

void FoodDatabase::RecipeParser::SkipWhiteSpace()
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    while( workString.at( pos ) == ' ' ) {
        pos++;
    }
}

std::string FoodDatabase::RecipeParser::ReadToken( const string &delim )
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    //find next delim
    auto p = workString.find_first_of( delim, pos );
    string out = workString.substr( pos, p - pos );
    p++;
    pos = p;

    return out;
}

bool FoodDatabase::RecipeParser::ExpectSymbol( char s )
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    return workString.at( pos++ ) == s;
}

char FoodDatabase::RecipeParser::Peek()
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    return workString.at( pos );
}