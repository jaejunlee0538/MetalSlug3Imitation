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
		configFile�� �о� SpriteManager���� ��������Ʈ�� �޾ƿ� 
		�ִϸ��̼� ��ü�� �����Ѵ�.
		*/
		void loadFromJSON(const std::string& configFile);
		void addAnimation(const std::string& name, SpritesAnimation* animation);
		void saveToJSON(const std::string& outputConfigFile);
		bool hasAnimation(const std::string& name);
		/*
		name �ִϸ��̼� ��ü�� �����͸� ��ȯ�Ѵ�.
		����� ���� �ִϸ��̼� ��ü�� �ݵ�� clearActive�� ȣ�����־�� �Ѵ�.
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