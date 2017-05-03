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
		configFile�� �о� SpriteManager���� ��������Ʈ�� �޾ƿ� 
		�ִϸ��̼� ��ü�� �����Ѵ�.
		*/
		void loadFromJSON(const std::string& configFile);
		void addAnimation(const std::string& name, SpritesAnimation* animation);
		SpritesAnimation* findAnimation(const std::string& name);
	private:
		AnimationMap _animationMap;
	};

}