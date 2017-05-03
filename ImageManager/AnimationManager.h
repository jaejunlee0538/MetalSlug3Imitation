#pragma once
#include <SingletonBase.h>
#include "SpritesAnimation.h"
#include <unordered_map>
#include <string>
namespace SGA {
	class AnimationManager : public SingletonBase<AnimationManager>
	{
		typedef std::unordered_map<std::string, SpritesAnimation*> AnimationMap;
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
		SpritesAnimation* findAnimation(const std::string& name);
	private:
		AnimationMap _animationMap;
	};

}