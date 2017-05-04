#include "GameWorld.h"
#include <assert.h>
#include "Stdafx.h"
#include <algorithm>
#include "SpriteManager.h"
#include "WorldClock.h"
#include <AnimationManager.h>
#include <SpritesAnimation.h>
GameWorld::GameWorld()
{
	GAME_WORLD = this;
}

GameWorld::~GameWorld()
{
	for (auto it = _animation.begin(); it != _animation.end(); ++it) {
		delete it->animation;
	}
}

HRESULT GameWorld::init() {
	GameNode::init();
	SGA::BitmapImage::setHWND(_hWnd);
	SPRITE_MANAGER->loadFromJSON("TestSprite.json");
	SGA::AnimationManager::getSingleton()->loadFromJSON("TestAnimation.json");
	_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_UpperRight"), {100, 100} });
	_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_LowerRight"),{ 100, 100 } });

	_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_UpperLeft"),{ 150, 100 } });
	_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_LowerLeft"),{ 150, 100 } });

	return S_OK;
}


void GameWorld::release(void) {

	GameNode::release();
}

void GameWorld::update(float dt) {
	GameNode::update(dt);
	GET_GAME_WORLD_CLOCK()->updateClock(dt*1000);
	if (GET_GAME_WORLD_CLOCK()->getCurrentTimeMillis() > 400) {
		static bool first_run = true;
		if (first_run) {
			first_run = false;
			_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_UpperRight"),{ 100, 150 } });
			_animation.push_back({ SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_LowerRight"),{ 100, 150 } });
		}
	}
	for (auto it = _animation.begin(); it != _animation.end(); ++it) {
		it->animation->update();
	}
}

void GameWorld::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	for (auto it = _animation.begin(); it != _animation.end(); ++it) {
		it->animation->render(hdc, it->drawPos.x, it->drawPos.y);
	}
}
