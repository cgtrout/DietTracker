#include "AllTests.h"
#include "Test.h"
#include "Test_CTString.h"

Tester tester;

void AllTests::addSuites() {
	Test_CTString::addTests();
}