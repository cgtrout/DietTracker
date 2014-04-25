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
    vector<string> lines = parseCommandLine( line );
    string commandName = lines[0];
    
    //convert commandName to lowercase
    std::transform( commandName.begin(), commandName.end(), commandName.begin(), ::tolower );
    
    //make sure command exists
    if( !dietCommands.DoesCommandExist( commandName ) ) {
        throw invalid_argument( "Command does not exist" );
    }

    auto &thiscommand = dietCommands.commands[ commandName ];
    auto lineIter = lines.begin();
    lineIter++;
    
    //set parameters
    for( auto &p: thiscommand.params ) {
        try {
            p->SetValue( *lineIter );
        } catch( invalid_argument &e ) {
            cout << commandName << ": Invalid parameter ( " << p->name << ")" << endl;
            throw invalid_argument( "Invalid parameter" );
        }
        ++lineIter;
    }

    //run function
    thiscommand.commandFunction();
}

void DietSystem::BindFunctions()
{
    BindFunction( "eat", std::bind( &DietSystem::Command_Eat, this ));
    dietCommands.commands[ "eat" ].AddParam( "FoodName", make_unique<Name>( Name( "notset" ) ) );
    dietCommands.commands[ "eat" ].AddParam( "Quantity", make_unique<Quantity>( Quantity( "0" ) ) );
}

void DietSystem::BindFunction( const std::string &s, std::function<void()> f )
{
    dietCommands.AddDietCommand( s );
    dietCommands.commands[ s ].commandFunction = f;
}

//command functions
void DietSystem::Command_Eat()
{
    auto &thiscommand = dietCommands.commands[ "eat" ];
    
}