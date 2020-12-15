#pragma once

#include <string>

static constexpr int DEFAULT_WIDTH = 120;
static constexpr double DEFAULT_HWRATIO = 2.2;

static constexpr auto HELP_STR1 = "-h";
static constexpr auto HELP_STR2 = "--help";

static constexpr auto WIDTH_STR1 = "-w";
static constexpr auto WIDTH_STR2 = "--width";

static constexpr auto RATIO_STR1 = "-r";
static constexpr auto RATIO_STR2 = "--ratio";

struct Arguments
{
	std::string Path;
	int Width;
	double Ratio;
};

class ArgParser
{
private:
	enum class State
	{
		Default = 0,
		Width,
		Ratio
	};
	State m_State;
	std::string m_Path;
	int m_Width;
	double m_Ratio;
	int m_Argc;
	char **m_Argv;

public:
	ArgParser() = delete;
	ArgParser(int argc, char **argv);
	Arguments ParseArguments();

private:
	void PrintHelpTextAndExit();
};