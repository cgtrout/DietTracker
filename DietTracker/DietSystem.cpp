#include <algorithm>

#include "DietSystem.h"
#include "CTString.h"
#include "CTException.h"
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
    string commandName = param_tokens[0];
    param_count = param_tokens.size() - 1;
    
    //convert commandName to lowercase
    //TODO pull this to seperate function?
    std::transform( commandName.begin(), commandName.end(), commandName.begin(), ::tolower );
    
    //make sure command exists
    if( !dietCommands.DoesCommandExist( commandName ) ) {
        throw invalid_argument( "Command does not exist" );
    }

    InitializeCommand( commandName );

    //run function
    cout << "Executing function: " << commandName << endl;
    thiscommand->commandFunction();
}

void DietSystem::BindFunctions()
{
    BindFunction( "eat", std::bind( &DietSystem::Command_Eat, this ) );
    BindFunction( "define", std::bind( &DietSystem::Command_Define, this ) );
    BindFunction( "printfood", std::bind( &DietSystem::Command_PrintFood, this ) );
    BindFunction( "printlogs", std::bind( &DietSystem::Command_PrintLogs, this ) );

    BindFunction( "delete", std::bind( &DietSystem::Command_Delete, this ) );
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

/* 
 *   command functions
 *
 */

//Eat name quantity (auto-time)
void DietSystem::Command_Eat()
{
    if( param_count != 2 && param_count != 3 ) {
        throw invalid_argument( "Wrong number of params" );
    }
    
    Name foodName{ *tokens_iter++ };
    Quantity quantity{ *tokens_iter++ };
    //TODO validate quantity to ensure it is only in grams
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
}

//Define Chocolate	  serving_size(g)	calories_per_serving	//define new food.  Maybe make this a multi prompt command
//Define SandwichSoup { Beef_Sandwich=1s, campells_chicken=100g }	//brackets denote we want to create a 'recipe'
//
//Define food servingSize caloriesPerServing
//define Recipe { recipe spec }
void DietSystem::Command_Define()
{
    if( param_count != 2 && param_count != 3 ) {
        throw invalid_argument( "Wrong number of params" );
    }

    bool isRecipe = param_tokens[ 2 ].at( 0 ) == '{';

    if( isRecipe ) {
        if( param_count != 2 ) {
            throw invalid_argument( "Wrong number of params" );
        }
        foodDatabase.AddRecipe( param_tokens[1], param_tokens[ 2 ] );
    } else {
        if( param_count != 3 ) {
            throw invalid_argument( "Wrong number of params" );
        }
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
    cout << "\n" << "Printing Logs" << "\n\n";
    dailyLog.PrintLogs();
}

void DietSystem::Command_Delete()
{
    throw NotYetImplementedException();
}