#pragma once
#include "SingletonBase.h"
#include "SpritesAnimation.h"
#include <map>
#include <string>
#include <array>
namespace SGA {
	class AnimationManager : public SingletonBase<AnimationManager>
	{
		typedef std::array<SpritesAnimation*, 20> AnimationPool;
		typedef std::map<std::string, AnimationPool*> AnimationMap;
	public:
		AnimationManager();
		~AnimationManager();
		void clearAll();
		/*
		configFile을 읽어 SpriteManager에서 스프라이트를 받아와 
		애니메이션 객체를 생성한다.
		*/
		void loadFromJSON(const std::string& configFile);
		void addAnimation(const std::string& name, SpritesAnimation* animation);
		void saveToJSON(const std::string& outputConfigFile);
		bool hasAnimation(const std::string& name);
		/*
		name 애니메이션 객체의 포인터를 반환한다.
		사용이 끝난 애니메이션 객체는 반드시 clearActive를 호출해주어야 한다.
		*/
		SpritesAnimation* findAnimation(const std::string& name);
	private:
		SpritesAnimation* findInactiveAnimation(AnimationPool& animationPool);
		bool isLRPair(std::string name1, std::string name2);
	private:
		AnimationMap _animationMap;
	};
#define GET_ANIMATION_MANAGER()	SGA::AnimationManager::getSingleton()
}