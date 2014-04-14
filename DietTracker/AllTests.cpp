#include "AllTests.h"
#include "Test.h"
#include "Test_CTString.h"
#include "Test_DietCommand.h"

Tester tester;

void AllTests::addSuites() {
	Test_CTString::addTests();
	Test_DietCommand::addTests();
}