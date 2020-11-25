#pragma once

#include <Windows.h>

class ConsoleController
{
private:
	DWORD m_DefaultInMode;
	DWORD m_DefaultOutMode;
	HANDLE m_HStdin;
	HANDLE m_HStdout;
	bool m_Init;

public:
	ConsoleController();
	~ConsoleController();
	inline void EnableVT() const { SetConsoleMode(m_HStdout, m_DefaultOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); }
	inline void RestoreDefaults() const { SetConsoleMode(m_HStdout, m_DefaultOutMode); }
	inline bool IsVTAlreadyOn() const { return m_DefaultOutMode == (m_DefaultOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); }
};