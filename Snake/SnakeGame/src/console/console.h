#pragma once
#ifndef CUSTOM_LOGGER
#define CUSTOM_LOGGER

//include libraries that are needed
#include <fstream>
#include <iostream>
#include <string>
#include <cstdarg>


//class for the console
class Console
{
public:
	//define functions
	void Log(const std::string&);
	
	void Log(const char* format, ...);

	void LogAndFile(const std::string&);

	void LogAndFile(const char* format, ...);

	int Pause();

	Console& operator <<(const std::string&);

	static Console* GetConsole();

private:
	Console();								//constructor

	Console(const Console&) {};             // copy constructor

	Console& operator=(const Console&) { return *this; };  // assignment operator 
	
	static const std::string m_sFileName;

	static Console* This;

	static std::ofstream Note;
};
#endif