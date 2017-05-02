#pragma once
#include <Windows.h>
#include "BitmapImage.h"
namespace SGA {
	/*
	아틀라스 이미지 _imageSource내의 스프라이트 조각을 나타내는 클래스.
	*/
	class Sprite
	{
		struct tagClippingInfo {
			int clipPosX, clipPosY;
			int pivotX, pivotY;
			int w, h;
		};
	public:
		Sprite(const BitmapImage* imgSrc, const BitmapImage* imgSrcMirror,
			const TCHAR* spriteName,
			int clipPosX, int clipPosY,
			int clipWidth, int clipHeight,
			float px, float py);

		virtual ~Sprite();

		/*
		스프라이트의 pivotPoint가 drawPos와 일치하도록 그린다.
		*/
		void render(HDC hdc, int drawPosX, int drawPosY, bool mirrored =false) const;

		inline const TCHAR* getName() const {
			return _spriteName;
		}
	private:
		//아틀라스 이미지내에서의 위치와 크기
		tagClippingInfo _clip;
		tagClippingInfo _clipMirror;

		//스프라이트 이름
		const TCHAR* _spriteName;
		const BitmapImage* _imageSource;
		const BitmapImage* _imageSourceMirror;
	};

}