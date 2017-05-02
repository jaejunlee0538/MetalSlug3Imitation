#include "GameWorld.h"
#include <assert.h>
#include "Stdafx.h"
#include <algorithm>
#include "SpriteManager.h"
#include "WorldClock.h"

GameWorld::GameWorld()
{
	GAME_WORLD = this;
}

GameWorld::~GameWorld()
{

}

HRESULT GameWorld::init() {
	GameNode::init();
	SGA::BitmapImage::setHWND(_hWnd);
	SPRITE_MANAGER->loadFromXMLFile("ABC.json");

	_player = new Player();
	_player->setPosition(300, 300);
	return S_OK;
}

void GameWorld::processKeyInput()
{

}

void GameWorld::release(void) {

	GameNode::release();
}

void GameWorld::update(float dt) {
	GameNode::update(dt);
	SGA::WorldClock::getSingleton()->updateClock();

	_player->update();
	processKeyInput();
}

void GameWorld::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	_player->render(hdc);
}
