#include <numeric>
#include <fstream>
#include <cassert>

#include "DietStorage.h"
#include "CTException.h"

/* Recipe Item
 * 
 *  Implementation
 */
float RecipeItem::CalculateGrams( float calories ) const
{
    float grams_per_serving = GetGramsPerServing();
    float total_calories = CalculateCalories( Quantity( "1.0s" ) );
    float grams_per_cal = grams_per_serving / total_calories;
    
    float calculated_grams = grams_per_cal * calories;
    return calculated_grams;
}

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

string Food::GenerateCommandString() const
{
    string out{ "Define " };
    out += name + " " + std::to_string( servingSize ) + " " + std::to_string( caloriesPerServing );
    return out;
}

float Food::CalculateCalories( const Quantity& quantity ) const
{
    if( quantity.GetType() == 's' ) {
        return quantity.GetFloatValue() * caloriesPerServing;
    } else if ( quantity.GetType() == 'g' ) {
        float gram_per_serving = caloriesPerServing / servingSize;
        return quantity.GetFloatValue() * gram_per_serving;
    }
    throw runtime_error( "Food::CalculateCalories runtime error" );
    return 0.0f;
}

/*
 *  Recipe Class
 *   Implemenation
 */

//constructors
Recipe::Recipe( const string &iname )
    : RecipeItem( iname )
{}

string Recipe::GenerateCommandString() const
{
    string out{ "define " };
    out += "{ ";
    size_t i = 0;
    int size = components.size();
    for( auto& comp : components ) {
        out += comp->item->GetName() + "=";
        out += comp->quantity.GetValue();
        if( i != size-1 ) {
            out += ", ";
        }
        i++;
    }
    out += " }";
    return out;
}

//AddRecipeComponent
void Recipe::AddRecipeComponent( RecipeItem *item, Quantity quant )
{
    components.push_back( make_unique<RecipeComponent>( item, quant ) );
}

float Recipe::CalculateCalories( const Quantity& quantity ) const
{
    float total_calories{};
    float total_grams{};

    for( auto& component : components ) {
        total_calories += component->CalculateCalories();

        switch( component->quantity.GetType() ) {
        case 's':
            total_grams += component->quantity.GetFloatValue() * component->item->GetGramsPerServing();
            break;
        case 'g':
            total_grams += component->quantity.GetFloatValue();
            break;
        default:
            throw runtime_error( "Invalid quantity type in component" );
        }
    }

    switch( quantity.GetType() ) {
    case 's':
        return total_calories * quantity.GetFloatValue();
    case 'g':
        return ( total_calories * quantity.GetFloatValue() ) / total_grams;
    default:
        throw runtime_error( "Invalid quantity type" );
    }
    
    return 0.0f;
}

float Recipe::GetGramsPerServing() const
{
    float grams{};
    for( auto& component : components ) {
        switch( component->quantity.GetType() ) {
        case 's':
            grams += component->item->GetGramsPerServing() * component->quantity.GetFloatValue();
            break;
        case 'g':
            grams += component->quantity.GetFloatValue();
            break;
        default:
            throw runtime_error( "Invalid quantity type" );
        }
    }
    return grams;
}

bool Recipe::IsLinkedTo( const RecipeItem *item ) const 
{
    for( auto& comp : components ) {
        if( comp->item == item ) {
            return true;
        }
    }
    return false;
}

/*
 *  DietEntry Class
 *   Implemenation
 */
DietEntry::DietEntry( RecipeItem *iitem, Quantity quant, Time itime )
    : quantity( quant )
    , item( iitem )
    , mtime( itime.GetValue() )
{}

DietEntry::DietEntry( DietEntry &&entry )
    : item( std::move( entry.item ) )
    , mtime( std::move(entry.mtime ) )
{}

/*
 *  DailyLogs Class
 *   Implemenation
 */
void DailyLog::AddEntry( unique_ptr<DietEntry> entry )
{
    entries.push_back( ( std::move( entry ) ) );
}

float DailyLog::CalculateCalories() const
{
    float total = std::accumulate( entries.begin(), entries.end(), 0.0f, []( float res, const unique_ptr<DietEntry>& entry ) {
        return res += entry->CalculateCalories();
    });

    return total;
}

void DailyLog::PrintLogs()
{
    for( auto& i : entries ) {
        cout << i->item->GetName();
        cout << " Quantity: " << i->quantity.GetValue();
        cout << " Calories: " << i->CalculateCalories();
        cout << " Time: " << i->mtime;
        cout << "\n";
    }
}

void DailyLog::WriteFile( const string& filename ) const 
{
    ofstream stream{ filename };
    if( stream.bad() ) {
        throw runtime_error( "Error writing file" );
    }
    for( auto& e : entries ) {
        stream << e->GenerateCommandString() << "\n";
    }
}

void DailyLog::SetDailyCalories( float value )
{
    assert( value > 0.0f );
    daily_calories = value;
}

void DailyLog::ReadDailyCalories( const string& filename )
{
    ifstream stream{ filename };
    if( stream.bad() ) {
        throw runtime_error( "Error writing file" );
    }
    float value{};
    stream >> value;
    SetDailyCalories( value );

    cout << "Read DailyCalories file" << "\n";
}
/*
 *  DailyLogs Class
 *   Implemenation
 */
void FoodDatabase::AddFood( unique_ptr<RecipeItem> item )
{
    CheckAlreadyExists( item->GetName() );
    database.push_back( std::move( item ) );
}

//"define recipe { food1=1s, food2=1s }"
void FoodDatabase::AddRecipe( const string &name, const string &recipe_str )
{
    CheckAlreadyExists( name );
    
    auto new_recipe = make_unique<Recipe>( name );

    //parse string
    RecipeParser parser{ recipe_str };

    //recipe must start with '{'
    parser.ExpectSymbol( '{' );

    int param_num = 1;

    while( true ) {
        parser.SkipWhiteSpace();

        //read name token
        auto token_name = parser.ReadToken( ",= {}" );

        //validate that food item exists in database
        RecipeItem *item = FindRecipeItem( token_name );
        if( item == nullptr ) {
            string errormsg{ "Food item does not exist: Param " };
            errormsg += to_string( param_num );
            throw invalid_argument( errormsg );
        }
        if( parser.Peek() == '=' ) {
            parser.ExpectSymbol( '=' );
            parser.SkipWhiteSpace();

            //read quantity
            string token_quant = parser.ReadToken( ",= {}" );

            //validate quantity
            Quantity quantity{ token_quant };

            //add to recipe
            new_recipe->AddRecipeComponent( item, quantity );
        } else {
            //assume quantity of 1
            new_recipe->AddRecipeComponent( item, Quantity( "1.0s" ) );
        }
        
        parser.SkipWhiteSpace();
        
        //if a ',' expect more food items, else if a '}' we are done
        char c = parser.Peek();
        if( c == ',' ) {
            parser.ExpectSymbol( ',' ); //this skips comma
        } else if( c == '}' ) {
            break;
        } else {
            string errormsg{ "Expected ',' or '}' after param " };
            errormsg += to_string( param_num );
            throw invalid_argument( errormsg );
        }
        param_num++;
    }
    //add recipe to database
    database.push_back( std::move( new_recipe ) );
}


void FoodDatabase::DeleteRecipeItem( const string& name )
{
    auto &db = database;
    
    //find pos
    auto iter = find_if( db.begin(), db.end(), [&name]( unique_ptr<RecipeItem>& i ) {
        return i->GetName() == name;
    });
    if( iter == db.end() ) {
        throw invalid_argument( "Recipe item given does not exist" );
    }
    
    //check if it is in use by recipe
    bool in_use = false;
    string used_item_name{};
    for( auto& r : db ) {
        if( r->IsLinkedTo( &(*iter->get()) ) ){
            used_item_name = r->GetName();
            in_use = true;
            break;
        }
    }
    if( in_use ) {
        string errormsg{ "Recipe item is in use by: " };
        errormsg += used_item_name;
        throw invalid_argument( errormsg );
    }
    //erase from vector
    database.erase( iter );
}

RecipeItem* FoodDatabase::FindRecipeItem( const string& name )
{
    auto& db = database;
    auto iter = find_if( db.begin(), db.end(), [&name]( unique_ptr<RecipeItem>& i ) {
        return i->GetName() == name;
    });
    if( iter == db.end() ) {
        return nullptr;
    } else {
        return iter->get();
    }
}

void FoodDatabase::PrintFood() const
{
    for( auto &i : database ) {
        cout << i->ToString() << "\n";
    }
}

void FoodDatabase::CheckAlreadyExists( const string& name ) const
{
    auto &db = database;
    auto iter = find_if( db.begin(), db.end(), [&name]( const unique_ptr<RecipeItem>& i ) {
        return i->GetName() == name;
    });
    if( iter != db.end() ) {
        throw invalid_argument( "Recipe item already exists" );
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
    
    //if delim not found return rest of string
    if( p == string::npos ) {
        return workString.substr( pos );  
    } 
    
    //else use delim to parse
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
        string errormsg = "Expected: ";
        errormsg += s;
        throw invalid_argument( errormsg );
    }
}

char FoodDatabase::RecipeParser::Peek()
{
    if( End() ) {
        throw out_of_range( "Parser at end");
    }
    return workString.at( pos );
}