#include "ArgParser.h"

#include "fmt/core.h"

ArgParser::ArgParser(int argc, char** argv)
    :m_State(State::Default), m_Path(""), m_Width(DEFAULT_WIDTH), m_Ratio(DEFAULT_HWRATIO),
    m_Argc(argc), m_Argv(argv)
{
}

Arguments ArgParser::ParseArguments()
{
    bool PathIsParsed = false;
    if(m_Argc == 1)
    {
        PrintHelpTextAndExit();
    }
    else
    {
        for(int i = 1; i < m_Argc; i++)
        {
            auto arg = std::string(m_Argv[i]);
            if(arg == HELP_STR1 || arg == HELP_STR2)
            {
                PrintHelpTextAndExit();
            }
            else if(arg == WIDTH_STR1 || arg == WIDTH_STR2)
            {
                m_State = State::Width;
            }
            else if(arg == RATIO_STR1 || arg == RATIO_STR2)
            {
                m_State = State::Ratio;
            }
            else
            {
                switch (m_State)
                {
                case State::Default:
                    if(!PathIsParsed)
                    {
                        m_Path = arg;
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
                    }
                    catch(const std::invalid_argument& e)
                    {
						fmt::print("Invalid Width\n");
                        PrintHelpTextAndExit();
                    }             
                    m_State = State::Default;
                    break;

                case State::Ratio:
                    try
                    {
                        m_Ratio = std::stod(arg);
                    }
                    catch(const std::invalid_argument& e)
                    {
						fmt::print("Invalid Ratio\n");
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
    
    if(PathIsParsed) return { m_Path, m_Width, m_Ratio };
    else PrintHelpTextAndExit();
}

void ArgParser::PrintHelpTextAndExit()
{
	fmt::print("Place Holder Help Text\n");
    exit(0); 
}