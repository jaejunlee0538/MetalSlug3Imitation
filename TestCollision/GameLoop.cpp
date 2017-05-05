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
#include "GameObjectLoop.h"
#include "MyCircle.h"
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
	GET_SPRITE_MANAGER()->addSprite("Ground.bmp", "Ground");
	GET_SPRITE_MANAGER()->addSprite("GroundCollided.bmp", "GroundCollided");
	GET_SPRITE_MANAGER()->addSprite("Circle50.bmp", "Circle50");
	GET_SPRITE_MANAGER()->addSprite("Circle50Collided.bmp", "Circle50Collided");
	SGA::CollisionComponent::disableCollisionBetweenLayers(SGA::COLLISION_LAYER1, SGA::COLLISION_LAYER2);
	SGA::CollisionComponent::disableCollisionBetweenLayers(SGA::COLLISION_LAYER3, SGA::COLLISION_LAYER3);
	SGA::TestBoxObject* controlledBox = new SGA::TestBoxObject({ -25,-25,25,25 }, { 350.0f,350.0f }, false, SGA::COLLISION_LAYER1, true, "CollisionBoxIdle", "CollisionBoxCollided");
	SGA::TestBoxObject* childBox = new SGA::TestBoxObject({ -25,-25,25,25 }, { -50.0f,0.0f }, false, SGA::COLLISION_LAYER2, false , "CollisionBoxIdle", "CollisionBoxCollided");
	controlledBox->addChild(childBox);
	controlledBox->disableGravity();

	SGA::MyCircle* myCircle = new SGA::MyCircle({ -25,-25,25,25 }, { 350.0f,350.0f }, false, SGA::COLLISION_LAYER1, true, "Circle50", "Circle50Collided");

	//_gameObjects.push_back(controlledBox);
	_gameObjects.push_back(myCircle);
	_gameObjects.push_back(new SGA::TestBoxObject({ -25,-25,25,25 }, { 160.0f,110.0f }, false, SGA::COLLISION_LAYER1, false, "CollisionBoxIdle", "CollisionBoxCollided"));
	_gameObjects.push_back(new SGA::TestBoxObject({ -25,-25,25,25 }, { 100.0f,250.0f }, true, SGA::COLLISION_LAYER1, false, "TriggerBoxIdle", "TriggerBoxTriggered"));
	_gameObjects.push_back(new SGA::TestBoxObject({ -25,-25,25,25 }, { 250.0f,250.0f }, true, SGA::COLLISION_LAYER2, false, "TriggerBoxIdle", "TriggerBoxTriggered"));

	SGA::TestBoxObject* ground =  new SGA::TestBoxObject({ -300,-20,300,20 }, { 250.0f,500.0f }, true, SGA::COLLISION_LAYER3, false, "Ground", "GroundCollided");
	ground->enableKinematic();
	_gameObjects.push_back(ground);
	SGA::TestBoxObject* ground2 = new SGA::TestBoxObject({ -300,-20,300,20 }, { 500.0f,480.0f }, true, SGA::COLLISION_LAYER3, false, "Ground", "GroundCollided");
	ground2->enableKinematic();
	_gameObjects.push_back(ground2);
	return S_OK;
}

void GameLoop::release(void) {
	GameNode::release();
}

void GameLoop::update(void) {
	GameNode::update();
	GET_REALTIME_CLOCK()->updateClock();
	GET_GAME_WORLD_CLOCK()->updateClock(UPDATE_DELTA_TIME);
	SGA::GameObjectLoop::gravityLoop(_gameObjects, { 0.0f, 200.0f }, GET_GAME_WORLD_CLOCK()->getDeltaTimeMillis()*0.001);
	SGA::GameObjectLoop::updateLoop(_gameObjects);
	SGA::GameObjectLoop::collisionCheckLoop(_gameObjects);
}

void GameLoop::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	GET_LAYER_MANAGER()->clearAllLayers();
	SGA::GameObjectLoop::renderLoop(_gameObjects);

	GET_LAYER_MANAGER()->render(hdc);
}
