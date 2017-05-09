#pragma once

#define WIN32_LEAN_AND_MEAN             
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <tchar.h>
#include <Global.h>
#include <CollisionConfig.h>
#define WIN_NAME	(TEXT("APIWindow"))
#define WIN_START_X	200
#define WIN_START_Y	100
#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	900
#define WIN_STYLE	CS_HREDRAW | CS_VREDRAW | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME

#define GET_GAME_WORLD		_gameWorld

void LogDebugMessage(const TCHAR* fmt, ...);

extern HWND _hWnd;
extern HINSTANCE _hInstance;