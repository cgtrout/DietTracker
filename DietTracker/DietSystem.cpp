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

    //ensure valid number of arguments 
    int defaultParam = thiscommand.hasDefaultParam;
    if( (lines.size() - 1) != (thiscommand.params.size() - defaultParam) ) {
        throw invalid_argument( "Incorrect number of params" );
    }
     
    auto lineIter = lines.begin();
    lineIter++;
    
    //set parameters
    for( auto parami = 0u; parami < thiscommand.params.size() - defaultParam; ++parami ) {
        auto &p = thiscommand.params[ parami ];
        try {
            p->SetValue( *lineIter );
        } catch( invalid_argument & ) {
            cout << commandName << ": Invalid parameter ( " << p->name << ")" << endl;
            throw invalid_argument( "Invalid parameter" );
        }
        ++lineIter;
    }

    //if last parm is a default, set it
    if( thiscommand.hasDefaultParam ) {
        thiscommand.GetLastParam()->SetDefault();
    }

    //run function
    thiscommand.commandFunction();
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

//command functions
void DietSystem::Command_Eat()
{
    auto &thiscommand = dietCommands.commands[ "eat" ];
    cout << "Executing eat command:" << "\n\n";

    //just print params for now
    for( auto &p : thiscommand.params ) {
        cout << p->name << " " << p->GetValue() << "\n";
    }

    Name *foodName = dynamic_cast<Name*>(thiscommand.params[ 0 ].get());
    Quantity *quantity = dynamic_cast<Quantity*>( thiscommand.params[ 1 ].get() );
    Time *time = dynamic_cast< Time* >( thiscommand.params[ 2 ].get() );

    //TODO
    //find out if given food / recipe exists

    //if it does not, add it

    //create entry and add it to dailyLog
}