#include "Sprite.h"
namespace SGA {
	Sprite::Sprite(const BitmapImage* imgSrc,
		const TCHAR* spriteName,
		int clipPosX, int clipPosY, int clipWidth, int clipHeight,
		float px, float py)
		:_imageSource(imgSrc),_spriteName(spriteName)
	{
		_clip.clipPosX = clipPosX;
		_clip.clipPosY = clipPosY;
		_clip.h = clipHeight;
		_clip.w = clipWidth;
		_clip.pivotX = clipWidth * px;
		_clip.pivotY = clipHeight * py;
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::render(HDC hdc, int drawPosX, int drawPosY) const
	{
		_imageSource->render(hdc,
			drawPosX - _clip.pivotX,
			drawPosY - _clip.pivotY,
			_clip.clipPosX, _clip.clipPosY,
			_clip.w, _clip.h);
	}
}