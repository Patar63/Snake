#include "console.h"
#include "utilities.h"

//makes a txt file to print a start up check to
const std::string Console::m_sFileName = "Bootup Check.txt";
Console* Console::This = NULL;
std::ofstream Console::Note;

Console::Console() 
{

}

Console* Console::GetConsole()
{
	if (This == NULL) 
	{
		This = new Console();
		Note.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
	}
	return This;
}

//makes an accurate log format inside Bootup Check.txt
void Console::Log(const std::string& message)
{
	std::cout << message << std::endl;
}

void Console::Log(const char * format, ...) 
{
	char* message = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string
	nLength = _vscprintf(format, args) + 1;
	message = new char[nLength];
	vsprintf_s(message, nLength, format, args);
	std::cout << Util::CurrentDateTime() << ":\t" << message << "\n";
	va_end(args);

	delete[] message;
}

void Console::LogAndFile(const std::string& message)
{

	std::cout << Util::CurrentDateTime() << ":\t" << message << "\n";

	Note << Util::CurrentDateTime() << ":\t";
	Note << message << "\n";
}

void Console::LogAndFile(const char * format, ...) //Needed function called in different ways, so I added multiple ways to construct
{
	char* message = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string
	nLength = _vscprintf(format, args) + 1;
	message = new char[nLength];
	vsprintf_s(message, nLength, format, args);

	//prints date 
	std::cout << Util::CurrentDateTime() << ":\t" << message << "\n";
	Note << Util::CurrentDateTime() << ":\t";
	Note << message << "\n";
	va_end(args);

	delete[] message;
}

int Console::Pause() //pause function
{
	return std::cin.get();
}

Console& Console::operator<<(const std::string& message)
{
	//uses current date to track when score was gotten
	Note << "\n" << Util::CurrentDateTime() << ":\t";
	Note << message << "\n";
	return *this;
}
