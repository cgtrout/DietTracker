#include "DietCommand.h"

void DietCommands::AddDietCommand(string &name) {
	commands.insert(make_pair(name, DietCommand(name)));
}