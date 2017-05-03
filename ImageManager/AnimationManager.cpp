#include "AnimationManager.h"
#include <assert.h>
#include <json.hpp>
#include "SpriteManager.h"
#include <fstream>
#include "SpriteManager.h"
namespace SGA {
	AnimationManager::AnimationManager()
	{
	}


	AnimationManager::~AnimationManager()
	{
	}

	void AnimationManager::clearAll()
	{
		for (auto it = _animationMap.begin(); it != _animationMap.end(); ++it) {
			delete it->second;
		}
		_animationMap.clear();
	}

	void AnimationManager::loadFromJSON(const std::string & configFile)
	{
		using json = nlohmann::json;
		std::ifstream file(configFile.c_str());
		assert(file.good());
		json jsonDoc;
		file >> jsonDoc;

		for (auto it = jsonDoc["animation"].begin(); it != jsonDoc["animation"].end(); ++it) {
			std::string animationName = (*it)["name"];
			int duration = (*it)["duration"];
			int maxReplayCount = (*it)["maxReplayCount"];
			bool mirrored = (*it)["mirrored"];
			std::vector<const Sprite*> sprites;
			sprites.reserve((*it)["sprites"].size());
			for (auto spriteName = (*it)["sprites"].begin(); spriteName != (*it)["sprites"].end(); ++spriteName) {
				const Sprite* sprite = SpriteManager::getSingleton()->findSprite(*spriteName);
				assert(sprite != NULL);
				sprites.push_back(sprite);
			}
			addAnimation(animationName, new SpritesAnimation(sprites, duration, maxReplayCount, mirrored));
		}
	}

	void AnimationManager::addAnimation(const std::string& name, SpritesAnimation * animation)
	{
		std::pair<AnimationMap::iterator, bool> result = 
			_animationMap.insert(std::make_pair(name, animation));
		if (result.second == false) {
			//이미 동일한 이름의 애니메이션이 등록되어 있어서 삽입할 수 없음
			assert(false);
		}
	}

	SpritesAnimation * AnimationManager::findAnimation(const std::string& name)
	{
		AnimationMap::iterator it = _animationMap.find(name);
		if (it == _animationMap.end()) {
			return NULL;
		}
		return it->second;
	}
}