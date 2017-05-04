#include "GameLoop.h"
#include <assert.h>
#include "Stdafx.h"
#include <algorithm>
#include "SpriteManager.h"
#include "WorldClock.h"
#include <AnimationManager.h>
#include <SpritesAnimation.h>
GameLoop::GameLoop()
{
	
}

GameLoop::~GameLoop()
{

}

HRESULT GameLoop::init() {
	GameNode::init();
	SGA::BitmapImage::setHWND(_hWnd);

	return S_OK;
}


void GameLoop::release(void) {

	GameNode::release();
}

void GameLoop::update(void) {
	GameNode::update();
	GET_REALTIME_CLOCK()->updateClock();

}

void GameLoop::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));

}
