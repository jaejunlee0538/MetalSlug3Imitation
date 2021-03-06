#include "Stdafx.h"
#include <stdio.h>
#include "GameWorld.h"
HWND _hWnd;
HINSTANCE _hInstance;
GameWorld* _gameWorld = NULL;

void LogDebugMessage(const TCHAR* fmt, ...) {

	static TCHAR szBuffer[2048]; // this here is a caveat!

	va_list args;

	va_start(args, fmt);
	_vstprintf_s(szBuffer, 2048, fmt, args);
	OutputDebugString(szBuffer);

	va_end(args);
}
