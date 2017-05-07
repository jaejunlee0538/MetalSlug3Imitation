#include "GameLoop.h"
#include <assert.h>
#include "Stdafx.h"
#include <algorithm>
#include <SpriteManager.h>
#include <WorldClock.h>
#include <AnimationManager.h>
#include <SpritesAnimation.h>
#include <LayerManager.h>
#include <GameObject.h>
#include <GameObjectLoop.h>
#include <string>
#include <ScrollingScene.h>
#include <CollisionConfig.h>
#include <AnimationManager.h>
#include <GroundRectangle.h>
#include <KeyManager.h>
#include <MapManager.h>
GameLoop::GameLoop()
{
	
}

GameLoop::~GameLoop()
{

}

HRESULT GameLoop::init() {
	GameNode::init();
	initCollisionLayer();

	GET_GAME_WORLD_CLOCK()->reset();
	GET_REALTIME_CLOCK()->reset();

	SGA::BitmapImage::setHWND(_hWnd);
	SGA::ScrollingScene * farScroll, *closeScroll;
	std::vector<SGA::GameObject*> grounds;
	std::vector<SGA::GameObject*> gameObjects;
	GET_MAP_MANAGER()->loadFromJSON("MapMission1Config.json", &farScroll, &closeScroll, grounds, gameObjects);

	_player = new SGA::TempPlayer();
	_player->setPosition(GET_CAMERA()->getPosition().x, GET_CAMERA()->getPosition().y);

	_gameObjects.push_back(GET_CAMERA());
	_gameObjects.push_back(_player);
	_gameObjects.push_back(farScroll);
	_gameObjects.push_back(closeScroll);
	_gameObjects.insert(_gameObjects.end(), grounds.begin(), grounds.end());
	_gameObjects.insert(_gameObjects.end(), gameObjects.begin(), gameObjects.end());

	GET_CAMERA()->setTarget(_player);
	return S_OK;
}

void GameLoop::release(void) {
	GameNode::release();
}

void GameLoop::update(void) {
	GameNode::update();
	GET_REALTIME_CLOCK()->updateClock();
	GET_GAME_WORLD_CLOCK()->updateClock(UPDATE_DELTA_TIME);
	//SGA::GameObjectLoop::updateLoop(_gameObjects);

	SGA::GameObjectLoop::gravityLoop(_gameObjects, { 0.0f, 50.0f }, GET_GAME_WORLD_CLOCK()->getDeltaTimeMillis()*0.001f);
	SGA::GameObjectLoop::updateLoop(_gameObjects);
	SGA::GameObjectLoop::collisionCheckLoop(_gameObjects);
}

void GameLoop::render(HDC hdc)
{
	GameNode::clearScreen(RGB(255, 255, 255));
	GET_LAYER_MANAGER()->clearAllLayers();
	SGA::GameObjectLoop::renderLoop(_gameObjects);

	///////////////////////////////////확대 출력/////////////////////////////////////////
	SGA::BitmapImage _buffer;
	_buffer.init(CAMERA_SIZE_X, CAMERA_SIZE_Y);
	_buffer.clearImage(RGB(0, 0, 0));
	GET_LAYER_MANAGER()->render(_buffer.getDC());//HDC대신 비트맵의 memDC를 넘겨주고, 

	//HDC에 StretchBlt를 이용하여 확대해서 그린다.
	_buffer.render(hdc,0,0, WIN_SIZE_X, WIN_SIZE_Y, 0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y);
}

void GameLoop::processKeyInput()
{
	if (GET_KEY_MANAGER()->isOnceKeyDown(VK_LBUTTON)) {
		POINT pt = getMousePosition();
	}
}
