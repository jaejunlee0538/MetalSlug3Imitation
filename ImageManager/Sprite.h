#pragma once
#include <Windows.h>
#include "BitmapImage.h"
namespace SGA {
	/*
	��Ʋ�� �̹��� _imageSource���� ��������Ʈ ������ ��Ÿ���� Ŭ����.
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
		��������Ʈ�� pivotPoint�� drawPos�� ��ġ�ϵ��� �׸���.
		*/
		void render(HDC hdc, int drawPosX, int drawPosY, bool mirrored =false) const;

		inline const TCHAR* getName() const {
			return _spriteName;
		}
	private:
		//��Ʋ�� �̹����������� ��ġ�� ũ��
		tagClippingInfo _clip;
		tagClippingInfo _clipMirror;

		//��������Ʈ �̸�
		const TCHAR* _spriteName;
		const BitmapImage* _imageSource;
		const BitmapImage* _imageSourceMirror;
	};

}