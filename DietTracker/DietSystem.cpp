#include <algorithm>
#include <fstream>

#include "DietSystem.h"
#include "CTString.h"
#include "CTException.h"

//help descriptions
static std::map <string, string> commandHelp { 
    { "eat", "[eat food_name quantity] - Add food to daily log" },
    { "define", "[define recipe recipe/str] or [define food quantity cals] - Define food - should not be used manually" },
    { "pfood", "[printfood] - Print list of food" },
    { "plog", "[printlogs] - Print list of items in daily log" },
    { "delete", "[delete food_name] - deletes food from system]" },
    { "dlast", "[deletelast] - delete last entry entered in daily log" },
    { "reload", "[reload] - reload FoodDefines file" },
    { "cals", "[cals] - prints total calories in log" },
    { "clog", "[clearlogs] - erases contents of the daily log" }
};

/* 
 * DietSystem class
 *
 * Implementation
 */

void DietSystem::ExecuteLine( const std::string &line )
{
    if( line.length() == 0 ) {
        throw invalid_argument( "Invalid command." );
    }
    param_tokens = parseCommandLine( line );
    if( param_tokens.empty() ) {
        return;
    }
    string commandName = param_tokens[0];
    param_count = param_tokens.size() - 1;
    
    //convert commandName to lowercase
    commandName = tolower_string( commandName );
    
    //make sure command exists
    if( !dietCommands.DoesCommandExist( commandName ) ) {
        throw invalid_argument( "Command does not exist" );
    }

    InitializeCommand( commandName );

    //run function
    thiscommand->commandFunction();
}

void DietSystem::ExecuteFile( const string& filename )
{
    cout << "Executing file: " << filename << "\n";
    cout << "======================================================" << "\n";
    
    ifstream s;
    s.open( filename );
    if( s.fail() ) {
        throw runtime_error( "Error loading file" );
    }
    int line_num = 1;
    string line{};
    while( getline( s, line ) ) {
        if( line.length() > 0 ) {
            try {
                ExecuteLine( line );
            } catch( exception& e ) {
                string errormsg{ "Error - line " };
                errormsg += to_string( line_num ) + ": " + e.what();
                throw runtime_error( errormsg );
            }
        }
        line_num++;
    }
}

void DietSystem::BindFunctions()
{
    BindFunction( "eat", std::bind( &DietSystem::Command_Eat, this ) );
    BindFunction( "define", std::bind( &DietSystem::Command_Define, this ) );
    BindFunction( "pfood", std::bind( &DietSystem::Command_PrintFood, this ) );
    BindFunction( "plog", std::bind( &DietSystem::Command_PrintLogs, this ) );

    BindFunction( "delete", std::bind( &DietSystem::Command_Delete, this ) );
    BindFunction( "dlast", std::bind( &DietSystem::Command_DeleteLast, this ) );
    BindFunction( "cals", std::bind( &DietSystem::Command_PrintCalories, this ) );
    BindFunction( "clog", std::bind( &DietSystem::Command_ClearLogs, this ) );
    BindFunction( "savelogs", std::bind( &DietSystem::Command_SaveLogs, this ) );
    BindFunction( "reload", std::bind( &DietSystem::Command_Reload, this ) );
    BindFunction( "help", std::bind( &DietSystem::Command_Help, this ) );
}

void DietSystem::BindFunction( const std::string &s, std::function<void()> f )
{
    dietCommands.AddDietCommand( s );
    dietCommands.commands[ s ].commandFunction = f;
}

void DietSystem::InitializeCommand( const string &name ) 
{
    thiscommand = &dietCommands.commands[ name ];
    tokens_iter = param_tokens.begin();
    tokens_iter++;
}

template <typename... Args>
void DietSystem::ValidateParamCount( size_t correct_count, const Args& ... rest ) const
{
    if( param_count != correct_count ) {
        ValidateParamCount( rest... );
    }
}

void DietSystem::ValidateParamCount( size_t correct_count ) const
{
    if( param_count != correct_count ) {
        throw invalid_argument( "Wrong number of params" );
    }
}

/* 
 *   command functions
 *
 */

//Eat name quantity (auto-time)
void DietSystem::Command_Eat()
{
    //must be 2 or 3
    ValidateParamCount( 2, 3 );
    
    Name foodName{ *tokens_iter++ };
    Quantity quantity{ *tokens_iter++ };
    unique_ptr<Time> time;
    
    if( param_count == 3 ) {
        time = make_unique<Time>( *tokens_iter );
    } else { //auto-time
        time = make_unique<Time>( GetCurrentTime() );
    }

    //find out if given food / recipe exists
    RecipeItem* item = foodDatabase.FindRecipeItem( foodName.GetValue() );
    if( item == nullptr ) {
        throw invalid_argument( "Recipe item does not exist" );
    }

    //create entry and add it to dailyLog
    auto dietEntry = make_unique<DietEntry>( item, quantity, time->GetValue() );
    dailyLog.AddEntry( std::move( dietEntry ) );

    WriteLogFile();
}

//Define Chocolate	  serving_size(g)	calories_per_serving	//define new food.  Maybe make this a multi prompt command
//Define SandwichSoup { Beef_Sandwich=1s, campells_chicken=100g }	//brackets denote we want to create a 'recipe'
//
//Define food servingSize caloriesPerServing
//define Recipe { recipe spec }
void DietSystem::Command_Define()
{
    ValidateParamCount( 2, 3 );

    bool isRecipe = param_tokens[ 2 ].at( 0 ) == '{';

    if( isRecipe ) {
        ValidateParamCount( 2 );
        foodDatabase.AddRecipe( param_tokens[1], param_tokens[ 2 ] );
    } else {
        ValidateParamCount( 3 );
        //handle as food
        string &name = param_tokens[ 1 ];
        float servingSize = stof( param_tokens[ 2 ] );
        float caloriesPerServing = stof( param_tokens[ 3 ] );

        auto food = make_unique<Food>( name, servingSize, caloriesPerServing );
        foodDatabase.AddFood( std::move( food ) );
    }
}

void DietSystem::Command_PrintFood()
{
    cout << "\n" << "Printing List of Food Items in Database" << "\n\n";
    foodDatabase.PrintFood();
}

void DietSystem::Command_PrintLogs()
{
    cout << "\n" << "Printing Logs" << "\n";
    cout << "================================" << "\n";
    dailyLog.PrintLogs();
}

void DietSystem::Command_Delete()
{
    ValidateParamCount( 1 );
    foodDatabase.DeleteRecipeItem( param_tokens[ 1 ] );
}

void DietSystem::Command_DeleteLast()
{
    if( !dailyLog.entries.empty() ) {
        dailyLog.entries.pop_back();
    } else {
        cout << "\n" << "No entries to delete. \n";
        return;
    }
    WriteLogFile();
    cout << "\n" << "Last log entry deleted\n";
}

void DietSystem::Command_PrintCalories()
{
    cout << "Daily Calories=" << dailyLog.CalculateCalories() << "\n";
}

void DietSystem::Command_ClearLogs()
{
    dailyLog.entries.clear();
    WriteLogFile();
    cout << "Logs cleared" << "\n";
}

void DietSystem::Command_SaveLogs()
{
    WriteLogFile();
    cout << "Daily log saved" << "\n";
}

void DietSystem::Command_Reload()
{
    //must clear both to ensure validation takes place
    foodDatabase.database.clear();
    dailyLog.entries.clear();
    try {
        ReadFoodDefine();
        ReadDailyLogs();
    } catch( exception& e ) {
        cout << "Error reloading files: " << e.what() << "\n";
    }
}

void DietSystem::Command_Help()
{
    for( auto& command : dietCommands.commands ) {
        const string& name = command.second.GetName();
        const string& description = commandHelp[ name ];
        cout << name << ": " << description << "\n\n";
    }
}