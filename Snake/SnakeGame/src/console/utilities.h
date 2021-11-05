#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <string>
#include <time.h>

namespace Util
{
	// gets date. Could be used to track scores time
	const std::string CurrentDateTime()
	{
		time_t now = time(NULL);
		struct tm tstruct;
		char buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}
}
#endif