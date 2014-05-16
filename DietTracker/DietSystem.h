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

    DietCommands dietCommands;
    DailyLog dailyLog;
    FoodDatabase foodDatabase;

private:

    //bind A function to dietCommands
    void BindFunction( const std::string &s, std::function<void()> f );

    void InitializeCommand( const string &name );

    std::vector<string>::iterator tokens_iter;
    vector<string> param_tokens;
    size_t param_count;

    DietCommand *thiscommand;

    //ensure user has given correct # of params
    //throws invalid_arg if param_count isn't correct
    //TODO set this up to allow multiple ints
    void ValidateParamCount( size_t correct_count ) const;

    //--COMMAND FUNCTIONS--
    void Command_Eat();
    void Command_Define();
    void Command_PrintFood();
    void Command_PrintLogs();
    
    void Command_Delete();      //deletes food item
};

#endif