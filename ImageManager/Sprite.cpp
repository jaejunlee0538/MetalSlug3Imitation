#include "Sprite.h"
namespace SGA {
	Sprite::Sprite(const BitmapImage* imgSrc, const BitmapImage* imgSrcMirror,
		const TCHAR* spriteName,
		int clipPosX, int clipPosY, int clipWidth, int clipHeight,
		float px, float py)
		:_imageSource(imgSrc), _imageSourceMirror(imgSrcMirror),
		_spriteName(spriteName)
	{
		_clip.clipPosX = clipPosX;
		_clip.clipPosY = clipPosY;
		_clip.h = clipHeight;
		_clip.w = clipWidth;
		_clip.pivotX = clipWidth * px;
		_clip.pivotY = clipHeight * py;
		
		_clipMirror.clipPosX = _imageSourceMirror->getWidth() - (clipPosX + clipWidth);
		_clipMirror.clipPosY = clipPosY;
		_clipMirror.h = clipHeight;
		_clipMirror.w = clipWidth;
		_clipMirror.pivotX = (1.0f - px) * clipWidth;
		_clipMirror.pivotY = py * clipHeight;
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::render(HDC hdc, int drawPosX, int drawPosY, bool mirrored) const
	{
		if (mirrored) {
		/*	_imageSource->render(hdc,
				drawPosX - (_w -_pivotX),
				drawPosY - (_h - _pivotY),
				_clipPosX, _clipPosY,
				_w, _h);*/
			//TODO : 이미지 어떻게 뒤집어서 출력하지?
			_imageSourceMirror->render(hdc,
				drawPosX - _clipMirror.pivotX,
				drawPosY - _clipMirror.pivotY,
				_clipMirror.clipPosX, _clipMirror.clipPosY,
				_clipMirror.w, _clipMirror.h);
		}
		else {
			_imageSource->render(hdc,
				drawPosX - _clip.pivotX,
				drawPosY - _clip.pivotY,
				_clip.clipPosX, _clip.clipPosY,
				_clip.w, _clip.h);
		}
	}
}