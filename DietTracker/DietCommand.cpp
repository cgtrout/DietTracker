#include "DietCommand.h"

void AddDietCommand(string name) {
	dietCommands.insert(make_pair(name, DietCommand(name)));
}