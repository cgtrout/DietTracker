#include "DietSystem.h"

/* 
 * DietSystem class
 *
 * Implementation
 */
void DietSystem::BindFunctions()
{
    BindFunction( "Eat", std::bind( &DietSystem::Command_Eat, this ));
    dietCommands.commands[ "Eat" ].AddParam( Quantity( "0" ) );
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