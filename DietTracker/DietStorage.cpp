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

//"define recipe { food1=1s, food2=1s }"
void FoodDatabase::AddRecipe( const string &name, const string &recipe )
{
    auto recipe_item = make_unique<Recipe>( name );

    //parse string
    RecipeParser parser{ recipe };

    //recipe must start with '{'
    parser.ExpectSymbol( '{' );

    while( true ) {
        parser.SkipWhiteSpace();
        
        //read name token
        auto token_name = parser.ReadToken( "= " );
        
        //TODO validate that food item exists in database
        

        parser.ExpectSymbol( '=' );
        parser.SkipWhiteSpace();

        string token_quant = parser.ReadToken( ", }" );
        parser.SkipWhiteSpace();

        //TODO validate quantity - set recipe component
        //TODO add to recipe

        //if a ',' expect more food items, else if a '}' we are done
        char c = parser.Peek();
        if( c == ',' ) {
            parser.ExpectSymbol( ',' ); //this skips comma
        } else if( c == '}' ) {
            break;
        } else {
            throw invalid_argument( "Expected ',' or '}'" );
        }
    }
    //todo add recipe
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
    
    auto p = workString.find_first_of( delim, pos );
    string out = workString.substr( pos, p - pos );  
    pos = p;

    return out;
}

void FoodDatabase::RecipeParser::ExpectSymbol( char s )
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    bool isSymbol = workString.at( pos++ ) == s;
    if( !isSymbol ) {
        throw invalid_argument( "Expected " + s );
    }
}

char FoodDatabase::RecipeParser::Peek()
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    return workString.at( pos );
}