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
		/*
		name 애니메이션 객체의 복사본 포인터를 반환한다.
		반환된 복사본은 사용 후 반드시 직접 삭제해주어야 한다.
		*/
		SpritesAnimation* findAnimation(const std::string& name);
	private:
		AnimationMap _animationMap;
	};

}