#pragma once
#include "SingletonBase.h"
#include "SpritesAnimation.h"
#include <unordered_map>
#include <string>
#include <array>
namespace SGA {
	class AnimationManager : public SingletonBase<AnimationManager>
	{
		typedef std::array<SpritesAnimation*, 20> AnimationPool;
		typedef std::unordered_map<std::string, AnimationPool*> AnimationMap;
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
		/*
		name �ִϸ��̼� ��ü�� �����͸� ��ȯ�Ѵ�.
		����� ���� �ִϸ��̼� ��ü�� �ݵ�� clearActive�� ȣ�����־�� �Ѵ�.
		*/
		SpritesAnimation* findAnimation(const std::string& name);
	private:
		SpritesAnimation* findInactiveAnimation(AnimationPool& animationPool);
	private:
		AnimationMap _animationMap;
	};
#define GET_ANIMATION_MANAGER()	SGA::AnimationManager::getSingleton()
}