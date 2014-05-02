#include <algorithm>

#include "DietSystem.h"
#include "CTString.h"
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
    //function eat
    BindFunction( "eat", std::bind( &DietSystem::Command_Eat, this ));

    //function define
    BindFunction( "define", std::bind( &DietSystem::Command_Define, this ) );
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
    
    auto foodName = make_unique<Name>( *tokens_iter++ );
    auto quantity = make_unique<Quantity>( *tokens_iter++ );
    unique_ptr<Time> time;
    
    if( param_count == 3 ) {
        time = make_unique<Time>( *tokens_iter );
    } else { //auto-time
        time = make_unique<Time>( GetCurrentTime() );
    }

    //TODO
    //find out if given food / recipe exists

    //create entry and add it to dailyLog
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
        //parse recipe string
        //auto recipe = make_unique<Recipe>();
        
    } else {
        //handle as food
        auto &name = param_tokens[ 1 ];
        auto servingSize = stof( param_tokens[ 2 ] );
        auto caloriesPerServing = stof( param_tokens[ 3 ] );

        auto food = make_unique<Food>( name, servingSize, caloriesPerServing );

        foodDatabase.AddFood( std::move( food ) );
    }
}