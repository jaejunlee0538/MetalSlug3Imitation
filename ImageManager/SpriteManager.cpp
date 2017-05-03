#include "SpriteManager.h"
#include <json.hpp>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
namespace SGA {
	SpriteManager::SpriteManager()
	{
	}


	SpriteManager::~SpriteManager()
	{
		clearAll();
	}

	void SpriteManager::clearAll()
	{
		//스프라이트 객체 모두 삭제
		for (auto it = _spriteMap.begin(); it != _spriteMap.end(); ++it) {
			delete it->second;
		}
		_spriteMap.clear();
		//아틀라스 객체 모두 삭제
		for (auto it = _atlasImageMap.begin(); it != _atlasImageMap.end(); ++it) {
			delete it->second.source;
			delete it->second.sourceFlipped;
		}
		_atlasImageMap.clear();
	}

	void SpriteManager::loadFromJSON(const std::string & configFile)
	{
		using json = nlohmann::json;
		std::ifstream file(configFile.c_str());
		assert(file.good());

		json jsonFile;
		file >> jsonFile;
		tagAtlasImage atlas = loadAtlasImage(jsonFile["meta"]["image"]);
		
		int x, y, w, h;
		float px, py;
		//std::string spriteName;
		for (auto it = jsonFile["frames"].begin(); it != jsonFile["frames"].end(); ++it) {
			std::string spriteName = (*it)["filename"];
			x = (*it)["frame"]["x"];
			y = (*it)["frame"]["y"];
			w = (*it)["frame"]["w"];
			h = (*it)["frame"]["h"];
			px = (*it)["pivot"]["x"];
			py = (*it)["pivot"]["y"];
			insertSprite(spriteName, new Sprite(atlas.source, atlas.sourceFlipped, spriteName.c_str(), x, y, w, h, px, py));
			//std::cout << x << " " << y << " " << w << " " << h << " " << px << " " << py << std::endl;
		}
	}

	void SpriteManager::addSprite(const std::string & imageFile, const std::string & spriteName)
	{
		tagAtlasImage atlas = loadAtlasImage(imageFile);
		Sprite* sprite = new Sprite(atlas.source, atlas.sourceFlipped, spriteName.c_str(), 0, 0,
			atlas.source->getWidth(), atlas.source->getHeight(), 0.5f, 0.5f);
		insertSprite(spriteName, sprite);
	}

	void SpriteManager::addSprite(const std::string & imageFile, const std::string & spriteName, int clipX, int clipY, int clipW, int clipH)
	{
		assert(false);
	}

	void SpriteManager::addSprite(const std::string & imageFile, const std::string & spriteName, int clipX, int clipY, int clipW, int clipH, int pivotX, int pivotY)
	{
		assert(false);
	}

	const Sprite * SpriteManager::findSprite(const std::string & key)
	{
		SpriteMap::iterator it = _spriteMap.find(key);
		if (it == _spriteMap.end()) {
			return NULL;
		}
		return it->second;
	}

	SpriteManager::tagAtlasImage SpriteManager::loadAtlasImage(const std::string & imageFile)
	{
		tagAtlasImage atlas;
		atlas.source = new BitmapImage();
		assert(atlas.source != NULL);
		assert(atlas.source->init(imageFile.c_str(), true, RGB(255, 0, 255)) == S_OK);
		atlas.sourceFlipped = BitmapImage::createMirroredImage(*atlas.source);
		auto result = _atlasImageMap.insert(std::make_pair(imageFile, atlas));
		assert(result.second == true);
		return atlas;
	}

	void SpriteManager::insertSprite(const std::string & key, Sprite * sprite)
	{
		assert(sprite != NULL);
		auto result = _spriteMap.insert(std::make_pair(key, sprite));
		assert(result.second == true);
	}
}