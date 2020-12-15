#include "ArgParser.h"

#include <filesystem>
#include "fmt/core.h"

// Becareful here about file system
#ifdef _MSC_VER
#if _MSC_VER > 1912
namespace fsys = std::filesystem;
#else
namespace fsys = std::experimental::filesystem;
#endif
#else
namespace fsys = std::filesystem;
#endif

ArgParser::ArgParser(int argc, char **argv)
	: m_State(State::Default), m_Path(""), m_Width(DEFAULT_WIDTH), m_Ratio(DEFAULT_HWRATIO),
	  m_Argc(argc), m_Argv(argv)
{
}

Arguments ArgParser::ParseArguments()
{
	bool PathIsParsed = false;
	if (m_Argc == 1)
	{
		PrintHelpTextAndExit();
	}
	else
	{
		for (int i = 1; i < m_Argc; i++)
		{
			auto arg = std::string(m_Argv[i]);
			if (arg == HELP_STR1 || arg == HELP_STR2)
			{
				PrintHelpTextAndExit();
			}
			else if (arg == WIDTH_STR1 || arg == WIDTH_STR2)
			{
				m_State = State::Width;
			}
			else if (arg == RATIO_STR1 || arg == RATIO_STR2)
			{
				m_State = State::Ratio;
			}
			else
			{
				switch (m_State)
				{
				case State::Default:
					if (!PathIsParsed)
					{
						m_Path = fsys::absolute(arg).string();
						PathIsParsed = true;
					}
					else
					{
						PrintHelpTextAndExit();
					}
					break;

				case State::Width:
					try
					{
						m_Width = std::stoi(arg);
						if (m_Width < 0)
						{
							fmt::print("Bad width value {0}. Defaulting to {1}.\n", m_Width, DEFAULT_WIDTH);
							m_Width = DEFAULT_WIDTH;
						}
					}
					catch (const std::invalid_argument)
					{
						fmt::print("Invalid Width [{}]. Width must be non-negative integer.\n\n", arg);
						PrintHelpTextAndExit();
					}
					m_State = State::Default;
					break;

				case State::Ratio:
					try
					{
						m_Ratio = std::stod(arg);
						if (m_Ratio <= 0.000001)
						{
							fmt::print("Bad ratio value {0}. Defaulting to {1}.\n", m_Ratio, DEFAULT_HWRATIO);
							m_Ratio = DEFAULT_HWRATIO;
						}
					}
					catch (const std::invalid_argument)
					{
						fmt::print("Invalid Ratio [{}]. Ratio must be postive float.\n\n", arg);
						PrintHelpTextAndExit();
					}
					m_State = State::Default;
					break;

				default:
					PrintHelpTextAndExit();
					break;
				}
			}
		}
	}

	if (PathIsParsed)
		return {m_Path, m_Width, m_Ratio};
	else
	{
		fmt::print("Path of image must be passed.\n\n");
		PrintHelpTextAndExit();
	}
}

void ArgParser::PrintHelpTextAndExit()
{
	fmt::print("TERMIMAGE || A Terminal image viewer for VT100 emulated terminals.\nWritten by Mohammad Ishrak Abedin.\n\n");
	fmt::print("POSITIONAL ARGUMENTS\n--------------------\n");
	fmt::print("[Path]\t\tPath of the image to view.\n\n");
	fmt::print("OPTIONAL ARGUMENTS\n------------------\n");
	fmt::print("[-w][--width]\tDesired width of the image. Try to match console size. (Default {})\n", DEFAULT_WIDTH);
	fmt::print("[-r][--ratio]\tCompression ratio of the image. Console character blocks are not perfect squares. (Default {})\n", DEFAULT_HWRATIO);
	fmt::print("[-h][--help]\tBring up help and close the application.\n");
	exit(0);
}