#pragma once

#define WIN32_LEAN_AND_MEAN             
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <tchar.h>
#include "RandomFunction.h"
#include "SpriteManager.h"
#include "WorldClock.h"
#include "KeyManager.h"
#include "GameWorld.h"
#define WIN_NAME	(TEXT("APIWindow"))
#define WIN_START_X	0
#define WIN_START_Y	0
#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	1100
#define WIN_STYLE	CS_HREDRAW | CS_VREDRAW | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME

#define TRANSPARENT_COLOR	RGB(255,0,255)

typedef std::basic_string<TCHAR> String;

#define RND		SGA::RandomFunction::getSingleton()
#define KEY_MANAGER	SGA::KeyManager::getSingleton()
//#define IMAGE_MANAGER	ImageManager::getSingleton()
#define SPRITE_MANAGER	SGA::SpriteManager::getSingleton()

#define GAME_WORLD		_gameWorld
#define ANIMATION_TIME	200

void LogDebugMessage(const TCHAR* fmt, ...);

extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern GameWorld* _gameWorld;