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
    vector<string> lines = parseCommandLine( line );
    auto &thiscommand = dietCommands.commands[ lines[ 0 ] ];
    
    auto iter = lines.begin(); iter++;
    auto i = 0;

    //set parameters
    for( ; iter != lines.end(); ++iter ) {
        thiscommand.params[ i ]->SetValue(*iter);
        i++;
    }

    //run function
    thiscommand.commandFunction();
}

void DietSystem::BindFunctions()
{
    BindFunction( "Eat", std::bind( &DietSystem::Command_Eat, this ));
    dietCommands.commands[ "Eat" ].AddParam( "FoodName", make_unique<Name>( Name( "notset" ) ) );
    dietCommands.commands[ "Eat" ].AddParam( "Quantity", make_unique<Quantity>( Quantity( "0" ) ) );
}

void DietSystem::BindFunction( const std::string &s, std::function<void()> f )
{
    dietCommands.AddDietCommand( s );
    dietCommands.commands[ s ].commandFunction = f;
}

//command functions
void DietSystem::Command_Eat()
{
    auto &thiscommand = dietCommands.commands[ "Eat" ];
    
}