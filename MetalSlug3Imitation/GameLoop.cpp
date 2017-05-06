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
	GET_LAYER_MANAGER()->init(CAMERA_SIZE_X, CAMERA_SIZE_Y);
	GET_SPRITE_MANAGER()->loadFromJSON(SPRITE_RESOURCE_PATH"MapMission1.json");
	GET_SPRITE_MANAGER()->loadFromJSON(SPRITE_RESOURCE_PATH"TarmaSprite.json");
	//GET_ANIMATION_MANAGER()->loadFromJSON(SPRITE_RESOURCE_PATH"TarmaAnimation.json");
	GET_CAMERA()->init(CAMERA_SIZE_X, CAMERA_SIZE_Y, CAMERA_INIT_POS_X, CAMERA_INIT_POS_Y);
	
	std::vector<const SGA::Sprite*> backGroundSprites;
	GET_SPRITE_MANAGER()->findSpriteList("BackgroundScene", backGroundSprites);
	assert(backGroundSprites.empty() == false);
	SGA::ScrollingScene * background = new SGA::ScrollingScene(backGroundSprites,
		GET_LAYER_MANAGER()->findLayer(SGA::LayerManager::LAYER_IDDEX_SCENE_BACKGROUND), 0.5088471f, 1.0f);
	std::vector<const SGA::Sprite*> foregroundSprites;
	GET_SPRITE_MANAGER()->findSpriteList("ForegroundScene", foregroundSprites);
	assert(foregroundSprites.empty() == false);
	SGA::ScrollingScene * foreground = new SGA::ScrollingScene(foregroundSprites,
		GET_LAYER_MANAGER()->findLayer(SGA::LayerManager::LAYER_INDEX_SCENE_WORLD), 1.0f, 1.0f);
	background->setCameraInitPos(GET_CAMERA()->getPosition().x, GET_CAMERA()->getPosition().y);
	foreground->setCameraInitPos(GET_CAMERA()->getPosition().x, GET_CAMERA()->getPosition().y);

	_player = new SGA::Player();
	_player->setPosition(CAMERA_INIT_POS_X, CAMERA_INIT_POS_Y);

	SGA::GroundRectangle * ground = new SGA::GroundRectangle(CAMERA_INIT_POS_X, CAMERA_INIT_POS_Y + 50, 250, 20);

	_gameObjects.push_back(ground);
	_gameObjects.push_back(background);
	_gameObjects.push_back(foreground);
	_gameObjects.push_back(GET_CAMERA());
	_gameObjects.push_back(_player);

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
	SGA::GameObjectLoop::updateLoop(_gameObjects);
	SGA::GameObjectLoop::gravityLoop(_gameObjects, { 0.0f, 50.0f }, GET_GAME_WORLD_CLOCK()->getDeltaTimeMillis()*0.001f);
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
