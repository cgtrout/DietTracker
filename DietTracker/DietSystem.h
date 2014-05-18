#ifndef DIETSYSTEM_H
#define DIETSYSTEM_H

#include <string>
#include <functional>

#include "DietCommand.h"
#include "DietStorage.h"

class DietSystem {
public:
    void ExecuteLine( const std::string &line );
    void ExecuteFile( const std::string& filename );
    void BindFunctions();

    DietCommands dietCommands;
    DailyLog dailyLog;
    FoodDatabase foodDatabase;

    string filePath;

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
    void ValidateParamCount( size_t correct_count ) const;
    
    template <typename... Args>
    void ValidateParamCount( size_t correct_count, const Args& ... rest ) const;

    //--COMMAND FUNCTIONS--
    void Command_Eat();
    void Command_Define();      //define food
    void Command_PrintFood();   //print list of food items
    void Command_PrintLogs();
    
    void Command_Delete();      //deletes food item
    void Command_PrintCalories();
    void Command_ClearLogs();    //clear dailylog
    void Command_SaveLogs();      //save dailyLog
};

#endif