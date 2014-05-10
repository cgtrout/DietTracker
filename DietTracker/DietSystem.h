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
    void Command_Define();
    void Command_PrintFood();
    void Command_PrintLogs();

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
};

#endif