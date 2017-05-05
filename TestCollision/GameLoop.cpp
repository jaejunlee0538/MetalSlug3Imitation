#include "GameLoop.h"
#include <assert.h>
#include "Stdafx.h"
#include <algorithm>
#include "SpriteManager.h"
#include "WorldClock.h"
#include <AnimationManager.h>
#include <SpritesAnimation.h>
#include <LayerManager.h>
#include <GameObject.h>
#include "TestBoxObject.h"
GameLoop::GameLoop()
{
	
}

GameLoop::~GameLoop()
{

}

HRESULT GameLoop::init() {
	GameNode::init();
	GET_GAME_WORLD_CLOCK()->reset();
	GET_REALTIME_CLOCK()->reset();
	SGA::BitmapImage::setHWND(_hWnd);
	GET_LAYER_MANAGER()->init(WIN_SIZE_X, WIN_SIZE_Y);
	GET_SPRITE_MANAGER()->addSprite("TriggerBoxIdle.bmp", "TriggerBoxIdle");
	GET_SPRITE_MANAGER()->addSprite("TriggerBoxTriggered.bmp", "TriggerBoxTriggered");
	GET_SPRITE_MANAGER()->addSprite("CollisionBoxIdle.bmp", "CollisionBoxIdle");
	GET_SPRITE_MANAGER()->addSprite("CollisionBoxCollided.bmp", "CollisionBoxCollided");

	_gameObjects.push_back(new SGA::TestBoxObject({ -50,-50,50,50 }, { 100.0f,100.0f }, false, SGA::COLLISION_LAYER1, true));
	_gameObjects.push_back(new SGA::TestBoxObject({ -50,-50,50,50 }, { 250.0f,100.0f }, false, SGA::COLLISION_LAYER1, false));
	_gameObjects.push_back(new SGA::TestBoxObject({ -50,-50,50,50 }, { 100.0f,250.0f }, true, SGA::COLLISION_LAYER1, false));
	_gameObjects.push_back(new SGA::TestBoxObject({ -50,-50,50,50 }, { 250.0f,250.0f }, true, SGA::COLLISION_LAYER2, false));
	return S_OK;
}

void GameLoop::release(void) {
	GameNode::release();
}

void GameLoop::update(void) {
	GameNode::update();
	GET_REALTIME_CLOCK()->updateClock();
	GET_GAME_WORLD_CLOCK()->updateClock(UPDATE_DELTA_TIME);
	for (int i = 0; i < _gameObjects.size(); ++i) {
		if (_gameObjects[i]->isActive()) {
			_gameObjects[i]->update();
		}
	}
	collisionCheck();
}

void GameLoop::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	GET_LAYER_MANAGER()->clearAllLayers();
	for (int i = 0; i < _gameObjects.size(); ++i) {
		if (_gameObjects[i]->isActive() && _gameObjects[i]->isRenderable()) {
			_gameObjects[i]->render();
		}
	}
	GET_LAYER_MANAGER()->render(hdc);
}

void GameLoop::collisionCheck()
{
	for (int i = 0; i < _gameObjects.size(); ++i) {
		if ((_gameObjects[i]->isActive() && _gameObjects[i]->isCollidable()) == false) {
			continue;
		}
		for (int k = i + 1; k < _gameObjects.size(); ++k) {
			if ((_gameObjects[k]->isActive() && _gameObjects[k]->isCollidable()) == false) {
				continue;
			}
			if (_gameObjects[i]->getCollisionComponent()->isCollidableWith(_gameObjects[k]->getCollisionComponent())) {
				if (_gameObjects[i]->getCollisionComponent()->isCollideWith(_gameObjects[k]->getCollisionComponent())) {
					_gameObjects[i]->getCollisionComponent()->handleCollision(_gameObjects[k]->getCollisionComponent());
					_gameObjects[k]->getCollisionComponent()->handleCollision(_gameObjects[i]->getCollisionComponent());
				}
				else {
					_gameObjects[i]->getCollisionComponent()->handleNoneCollision(_gameObjects[k]->getCollisionComponent());
					_gameObjects[k]->getCollisionComponent()->handleNoneCollision(_gameObjects[i]->getCollisionComponent());
				}
			}
		}
	}
}
