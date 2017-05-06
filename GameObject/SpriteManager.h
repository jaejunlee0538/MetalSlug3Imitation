#pragma once
#include <map>
#include <Windows.h>
#include "Sprite.h"
#include "BitmapImage.h"
#include "SingletonBase.h"
#include <vector>
namespace SGA {
	/*
	��Ʋ�� �̹����� ��������Ʈ �������� ����/�ʱ�ȭ/����/�˻��ϴ� ����� �����Ѵ�.
	*/
	class SpriteManager : public SingletonBase<SpriteManager>
	{
	private:
		struct tagAtlasImage {
			BitmapImage* source;
			BitmapImage* sourceFlipped;
		};
		//��������Ʈ Ŭ�� ���
		typedef std::map<std::string, Sprite*> SpriteMap;
		//��Ʋ�� �̹��� ���
		typedef std::map<std::string, tagAtlasImage> AtlasImageMap;
	public:
		SpriteManager();
		virtual ~SpriteManager();
		/*
		��� ��������Ʈ�� ��Ʋ�� �̹����� �����Ѵ�.
		*/
		void clearAll();
		void loadFromJSON(const std::string& configFile);
		void addSprite(const std::string& imageFile, const std::string& spriteName);
		void addSprite(const std::string& imageFile, const std::string& spriteName, int clipX, int clipY, int clipW, int clipH);
		void addSprite(const std::string& imageFile, const std::string& spriteName, int clipX, int clipY, int clipW, int clipH, int pivotX, int pivotY);
		
		/*
		namePrefix+"����"�� �̸��� ���� ��� ��������Ʈ�� sprites �����̳ʿ� ����ش�.
		*/
		void findSpriteList(std::string namePrefix, std::vector<const Sprite*>& sprites);
		/*
		key ��������Ʈ�� ���� ��ü �����͸� ��ȯ�Ѵ�.
		��������Ʈ ��ü�� SpriteManager��ü �Ҹ�ÿ� �����ȴ�.
		*/
		const Sprite* findSprite(const std::string& key);
	private:
		tagAtlasImage loadAtlasImage(const std::string& imageFile);
		void insertSprite(const std::string& key, Sprite* sprite);
	private:
		SpriteMap _spriteMap;
		AtlasImageMap _atlasImageMap;
	};
#define GET_SPRITE_MANAGER()	SGA::SpriteManager::getSingleton()
}