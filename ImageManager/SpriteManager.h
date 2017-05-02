#pragma once
#include <map>
#include <Windows.h>
#include "Sprite.h"
#include "BitmapImage.h"
#include "SingletonBase.h"
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
		void loadFromXMLFile(const std::string& xmlFile);
		void addSprite(const std::string& imageFile, const std::string& spriteName);
		void addSprite(const std::string& imageFile, const std::string& spriteName, int clipX, int clipY, int clipW, int clipH);
		void addSprite(const std::string& imageFile, const std::string& spriteName, int clipX, int clipY, int clipW, int clipH, int pivotX, int pivotY);
		const Sprite* findSprite(const std::string& key);
	private:
		tagAtlasImage loadAtlasImage(const std::string& imageFile);
		void insertSprite(const std::string& key, Sprite* sprite);
	private:
		SpriteMap _spriteMap;
		AtlasImageMap _atlasImageMap;
	};
}