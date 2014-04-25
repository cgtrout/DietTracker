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
};

#endif