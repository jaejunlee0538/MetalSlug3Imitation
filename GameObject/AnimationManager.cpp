#include "AnimationManager.h"
#include <assert.h>
#include "json.hpp"
#include "SpriteManager.h"
#include <fstream>
#include "CommonUtil.h"
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
			std::string animationNameFlip = animationName;
			bool loadFlipped = false;
			bool leftToRight;
			if (replaceLastString(animationNameFlip, "Right", "Left")){
				loadFlipped = true;
				leftToRight = false;
			}
			else if (replaceLastString(animationNameFlip, "Left", "Right")) {
				loadFlipped = true;
				leftToRight = true;
			}
			int duration = (*it)["duration"];
			int maxReplayCount = (*it)["maxReplayCount"];
			std::vector<const Sprite*> sprites;
			std::vector<const Sprite*> spritesFlipped;

			int spriteCount = (*it)["sprites"]["count"];
			std::string spriteNamePrefix = (*it)["sprites"]["prefix"];
			sprites.reserve(spriteCount);
			if (loadFlipped) {
				spritesFlipped.reserve(spriteCount);
			}
			for (int i = 0; i < spriteCount;++i) {
				std::string spriteName = spriteNamePrefix+"_"+std::to_string(i);
				const Sprite* sprite = GET_SPRITE_MANAGER()->findSprite(spriteName);
				assert(sprite != NULL);
				sprites.push_back(sprite);
				if (loadFlipped) {
					if (leftToRight) {
						replaceLastString(spriteName, "Left", "Right");
					}
					else {
						replaceLastString(spriteName, "Right", "Left");
					}
					const Sprite* sprite = GET_SPRITE_MANAGER()->findSprite(spriteName);
					assert(sprite != NULL);
					spritesFlipped.push_back(sprite);
				}
			}
			addAnimation(animationName, new SpritesAnimation(sprites, duration, maxReplayCount));
			if (loadFlipped) {
				addAnimation(animationNameFlip, new SpritesAnimation(spritesFlipped, duration, maxReplayCount));
			}
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