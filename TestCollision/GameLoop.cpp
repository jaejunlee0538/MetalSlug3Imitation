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
	SGA::CollisionComponent::disableCollisionBetweenLayers(SGA::COLLISION_LAYER1, SGA::COLLISION_LAYER2);

	SGA::TestBoxObject* controlledBox = new SGA::TestBoxObject({ -50,-50,50,50 }, { 350.0f,350.0f }, false, SGA::COLLISION_LAYER1, true);
	SGA::TestBoxObject* childBox = new SGA::TestBoxObject({ -50,-50,50,50 }, { -50.0f,0.0f }, false, SGA::COLLISION_LAYER2, false);
	controlledBox->addChild(childBox);
	_gameObjects.push_back(controlledBox);
	//_gameObjects.push_back(new SGA::TestBoxObject({ -50,-50,50,50 }, { 100.0f,100.0f }, false, SGA::COLLISION_LAYER1, true));
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
void renderRecursive(SGA::GameObject* object) {
	object->render();
	for (auto child = object->beginChilds(); child != object->endChilds(); ++child) {
		renderRecursive(*child);
	}
}
void GameLoop::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	GET_LAYER_MANAGER()->clearAllLayers();
	for (int i = 0; i < _gameObjects.size(); ++i) {
		if (_gameObjects[i]->isActive() && _gameObjects[i]->isRenderable()) {
			//_gameObjects[i]->render();
			renderRecursive(_gameObjects[i]);
		}
	}
	GET_LAYER_MANAGER()->render(hdc);
}

void checkCollisionComponent(SGA::CollisionComponent* collision1, SGA::CollisionComponent* collision2) {
	if (collision1->isCollidableWith(collision2)) {
		if (collision1->isCollideWith(collision2)) {
			collision1->handleCollision(collision2);
			collision2->handleCollision(collision1);
		}
		else {
			collision1->handleNoneCollision(collision2);
			collision2->handleNoneCollision(collision1);
		}
	}
}

void collisionCheckRecursion(SGA::GameObject* object1, SGA::GameObject* object2) {
	if ((object1->isActive() && object1->isCollidable()) == false) {
		return;
	}
	if ((object2->isActive() && object2->isCollidable()) == false) {
		return;
	}
	checkCollisionComponent(object1->getCollisionComponent(), object2->getCollisionComponent());
	for (auto child = object1->beginChilds(); child != object1->endChilds(); ++child) {
		collisionCheckRecursion(*child, object2);
	}
	for (auto child = object2->beginChilds(); child != object2->endChilds(); ++child) {
		collisionCheckRecursion(object1, object2);
	}
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
			collisionCheckRecursion(_gameObjects[i], _gameObjects[k]);
		}
	}
}
