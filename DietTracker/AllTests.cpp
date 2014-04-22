#include "AllTests.h"
#include "Test.h"
#include "Test_CTString.h"
#include "Test_DietCommand.h"
#include "Test_DietStorage.h"

Tester tester;

void AllTests::addSuites() {
	Test_CTString::addTests();
	Test_DietCommand::addTests();
    Test_DietStorage::addTests();
}