#include "MapManager.h"
#include "json.hpp"
#include "GroundRectangleRotated.h"
#include "ScrollingScene.h"
#include "SpriteManager.h"
#include "LayerManager.h"
#include "Camera.h"
#include "MathUtils.h"
#include <fstream>
#include <assert.h>
#include "FrontSprite.h"
namespace SGA {

	MapManager::MapManager()
	{
		
	}


	MapManager::~MapManager()
	{
	}

	void MapManager::loadFromJSON(std::string fileName, ScrollingScene** farScrollScene, ScrollingScene** closeScrollScene, 
		std::vector<GameObject*>& grounds, std::vector<GameObject*>& gameObjects)
	{
		std::ifstream file(fileName.c_str());
		assert(file.good());

		nlohmann::json config;
		file >> config;

		//init camera
		GET_CAMERA()->init(config["camera"]["size"]["width"], config["camera"]["size"]["height"], config["camera"]["initPos"]["x"], config["camera"]["initPos"]["y"]);
		GET_LAYER_MANAGER()->init(GET_CAMERA()->getCameraWidth(), GET_CAMERA()->getCameraHeight());
		//load background scene
		std::vector<const Sprite*> farSprites, closeSprites;
		GET_SPRITE_MANAGER()->loadFromJSON(config["backgroundSprites"]["file"]);
		GET_SPRITE_MANAGER()->findSpriteList(config["backgroundSprites"]["farBackground"]["prefix"], farSprites);
		assert(farSprites.size() == config["backgroundSprites"]["farBackground"]["count"]);
		GET_SPRITE_MANAGER()->findSpriteList(config["backgroundSprites"]["closeBackground"]["prefix"], closeSprites);
		assert(closeSprites.size() == config["backgroundSprites"]["closeBackground"]["count"]);

		ScrollingScene* farScroll = new ScrollingScene(farSprites,
			GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_IDDEX_SCENE_BACKGROUND),
			config["backgroundSprites"]["farBackground"]["scrollFactor"]["x"],
			config["backgroundSprites"]["farBackground"]["scrollFactor"]["y"]);
		ScrollingScene* closeScroll = new ScrollingScene(closeSprites,
			GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_WORLD),
			config["backgroundSprites"]["closeBackground"]["scrollFactor"]["x"],
			config["backgroundSprites"]["closeBackground"]["scrollFactor"]["y"]);

		farScroll->setCameraInitPos(GET_CAMERA()->getPosition().x, GET_CAMERA()->getPosition().y);
		closeScroll->setCameraInitPos(GET_CAMERA()->getPosition().x, GET_CAMERA()->getPosition().y);
	
		*farScrollScene = farScroll;
		*closeScrollScene = closeScroll;
		//calculate world size
		//TODO : 
		
		//load ground object
		grounds.reserve(config["groundRect"].size());
		for (auto it = config["groundRect"].begin(); it != config["groundRect"].end(); ++it) {
			auto field = *it;
			GroundRectangleRotated * groundRect = 
				new GroundRectangleRotated(field["pos"]["x"], field["pos"]["y"], 
					SGA::deg2rad(field["pos"]["angleDeg"]), field["size"]["width"], field["size"]["height"]);
			grounds.push_back(groundRect);
		}
		//일반 게임 오브젝트 로드(적, 구조물 등)

		for (auto it = config["spriteObject"].begin(); it != config["spriteObject"].end(); ++it) {
			auto ele = *it;
			SpriteObject* sprite = new SpriteObject(ele["name"], ele["isAnimation"], ele["pos"]["x"], ele["pos"]["y"],LayerManager::getLayerIndexFrom(ele["layer"]));
			gameObjects.push_back(sprite);
		}
		//TODO
	}
}