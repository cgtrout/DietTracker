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
    
    //convert commandName to lowercase
    //TODO pull this to seperate function?
    std::transform( commandName.begin(), commandName.end(), commandName.begin(), ::tolower );
    
    //make sure command exists
    if( !dietCommands.DoesCommandExist( commandName ) ) {
        throw invalid_argument( "Command does not exist" );
    }

    InitializeCommand( commandName );
    CheckParamCount( );

    //run function
    thiscommand->commandFunction();
}

void DietSystem::BindFunctions()
{
    //function eat
    BindFunction( "eat", std::bind( &DietSystem::Command_Eat, this ));
    dietCommands.commands[ "eat" ].AddParam( "FoodName", make_unique<Name>( Name( "notset" ) ) );
    dietCommands.commands[ "eat" ].AddParam( "Quantity", make_unique<Quantity>( Quantity( "0" ) ) );
    dietCommands.commands[ "eat" ].AddParam( "Time", make_unique<Time>( Time( "0:00" ) ) );
    dietCommands.commands[ "eat" ].hasDefaultParam = true;
    dietCommands.commands[ "eat" ].GetLastParam()->defaultFunction = []() { return GetCurrentTime(); };    
}

void DietSystem::BindFunction( const std::string &s, std::function<void()> f )
{
    dietCommands.AddDietCommand( s );
    dietCommands.commands[ s ].commandFunction = f;
}

void DietSystem::CheckParamCount()
{
    int defaultParam = thiscommand->hasDefaultParam;
    if( ( param_tokens.size( ) - 1 ) != ( thiscommand->params.size( ) - defaultParam ) ) {
        throw invalid_argument( "Incorrect number of params" );
    }
}

void DietSystem::InitializeCommand( const string &name ) 
{
    thiscommand = &dietCommands.commands[ name ];
    param_iter = thiscommand->params.begin();
    tokens_iter = param_tokens.begin();
    tokens_iter++;
}

void DietSystem::SetParam()
{
    ( *param_iter )->SetValue( *tokens_iter );
    param_iter++;
    tokens_iter++;
}

void DietSystem::SetDefaultParam()
{
    //run binded default function
    thiscommand->GetLastParam()->SetDefault();
}

void DietSystem::PrintParams()
{
    for( auto &p : thiscommand->params ) {
        cout << p->name << " " << p->GetValue( ) << "\n";
    }
}

//command functions
void DietSystem::Command_Eat()
{
    cout << "Executing eat command:" << "\n\n";

    SetParam();
    SetParam();
    SetDefaultParam();
    PrintParams();

    Name *foodName = dynamic_cast<Name*>( thiscommand->params[ 0 ].get( ) );
    Quantity *quantity = dynamic_cast<Quantity*>( thiscommand->params[ 1 ].get( ) );
    Time *time = dynamic_cast< Time* >( thiscommand->params[ 2 ].get( ) );

    //TODO
    //find out if given food / recipe exists

    //create entry and add it to dailyLog
}