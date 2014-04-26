#ifndef DIETSYSTEM_H
#define DIETSYSTEM_H

#include <string>
#include <functional>

#include "DietCommand.h"
#include "DietStorage.h"


class DietSystem {
public:
    void ExecuteLine( const std::string &line );
    void BindFunctions();
    
    //--COMMAND FUNCTIONS--
    void Command_Eat();
    //DEFINE
    //DELETE
    //etc...

    DietCommands dietCommands;
    DailyLog dailyLog;

private:

    //bind A function to dietCommands
    void BindFunction( const std::string &s, std::function<void()> f );

    void InitializeCommand( const string &name );

    //these set params from tokens_iter (and increment iter)
    
    //Sets param from tokens and moves iter
    void SetParam( );

    //Sets default param from tokens and moves iter
    void SetDefaultParam( );

    void CheckParamCount( );

    void PrintParams();
    
    //param variables
    std::vector<unique_ptr<CommandParamBase>>::iterator param_iter;
    std::vector<string>::iterator tokens_iter;
    vector<string> param_tokens;

    DietCommand *thiscommand;
};

#endif