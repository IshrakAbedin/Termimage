#include "ConsoleController.h"

#include "fmt/core.h"

ConsoleController::ConsoleController()
{
	m_HStdin = GetStdHandle(STD_INPUT_HANDLE);
	m_HStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(m_HStdin, &m_DefaultInMode);
	GetConsoleMode(m_HStdout, &m_DefaultOutMode);
}

ConsoleController::~ConsoleController()
{
}
