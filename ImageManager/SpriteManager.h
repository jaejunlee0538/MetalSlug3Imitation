#pragma once
#include <map>
#include <Windows.h>
#include "Sprite.h"
#include "BitmapImage.h"
#include "SingletonBase.h"
namespace SGA {
	/*
	아틀라스 이미지와 스프라이트 조각들을 생성/초기화/삭제/검색하는 기능을 제공한다.
	*/
	class SpriteManager : public SingletonBase<SpriteManager>
	{
	private:
		struct tagAtlasImage {
			BitmapImage* source;
			BitmapImage* sourceFlipped;
		};
		//스프라이트 클립 목록
		typedef std::map<std::string, Sprite*> SpriteMap;
		//아틀라스 이미지 목록
		typedef std::map<std::string, tagAtlasImage> AtlasImageMap;
	public:
		SpriteManager();
		virtual ~SpriteManager();
		/*
		모든 스프라이트와 아틀라스 이미지를 삭제한다.
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