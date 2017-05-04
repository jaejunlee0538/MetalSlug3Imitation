#pragma once

#define WIN32_LEAN_AND_MEAN             
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <tchar.h>

#define WIN_NAME	(TEXT("APIWindow"))
#define WIN_START_X	0
#define WIN_START_Y	0
#define WIN_SIZE_X	800
#define WIN_SIZE_Y	600
#define WIN_STYLE	CS_HREDRAW | CS_VREDRAW | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME

#define UPDATE_DELTA_TIME	30

#define TRANSPARENT_COLOR	RGB(255,0,255)

typedef std::basic_string<TCHAR> String;

#define GET_GAME_WORLD		_gameWorld

void LogDebugMessage(const TCHAR* fmt, ...);

extern HWND _hWnd;
extern HINSTANCE _hInstance;