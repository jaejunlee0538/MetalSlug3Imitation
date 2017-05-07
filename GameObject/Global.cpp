#include "Global.h"
#include <stdio.h>
#include <Windows.h>
void LogDebugMessage(const char* fmt, ...) {

	static char szBuffer[2048]; // this here is a caveat!

	va_list args;

	va_start(args, fmt);
	sprintf_s(szBuffer, 2048, fmt, args);
	OutputDebugString(szBuffer);

	va_end(args);
}
