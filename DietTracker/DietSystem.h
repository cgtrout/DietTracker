#ifndef DIETSYSTEM_H
#define DIETSYSTEM_H

#include <string>
#include <functional>

#include "DietCommand.h"
#include "DietStorage.h"


class DietSystem {
public:
    //--COMMAND FUNCTIONS--
    void Command_Eat();
    //DEFINE
    //DELETE
    //etc...

    //BindFunctions
    // binds all functions to dietCommands
    void BindFunctions();

    //bind A function to dietCommands
    void BindFunction( const std::string &s, std::function<void()> f );

    DietCommands dietCommands;
    DailyLog dailyLog;
};

#endif