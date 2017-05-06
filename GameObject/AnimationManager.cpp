#include "AnimationManager.h"
#include <assert.h>
#include "json.hpp"
#include "SpriteManager.h"
#include <fstream>
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
			std::vector<const Sprite*> sprites;
			sprites.reserve((*it)["sprites"].size());
			for (auto spriteName = (*it)["sprites"].begin(); spriteName != (*it)["sprites"].end(); ++spriteName) {
				const Sprite* sprite = GET_SPRITE_MANAGER()->findSprite(*spriteName);
				assert(sprite != NULL);
				sprites.push_back(sprite);
			}
			addAnimation(animationName, new SpritesAnimation(sprites, duration, maxReplayCount));
		}
	}

	void AnimationManager::addAnimation(const std::string& name, SpritesAnimation * animation)
	{
		AnimationMap::iterator it = _animationMap.find(name);
		assert(it == _animationMap.end());
		AnimationPool* pool = new AnimationPool;
		(*pool)[0] = animation;
		for (int i = 1; i < pool->size(); ++i) {
			(*pool)[i] = animation->clone();
		}
		_animationMap.insert(std::make_pair(name, pool));
	}

	SpritesAnimation * AnimationManager::findAnimation(const std::string& name)
	{
		AnimationMap::iterator it = _animationMap.find(name);
		assert(it != _animationMap.end());

		SpritesAnimation * animation = findInactiveAnimation(*(it->second));
		assert(animation != NULL);
		animation->restart();
		animation->setActive();
		return animation;
	}

	SpritesAnimation * AnimationManager::findInactiveAnimation(AnimationPool & animationPool)
	{
		for (int i = 0; i < animationPool.size(); ++i) {
			if (animationPool[i]->isActive() == false)
				return animationPool[i];
		}
		return NULL;
	}
}