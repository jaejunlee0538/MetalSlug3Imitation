#pragma once
#include <Windows.h>
#include "BitmapImage.h"
#include "SpriteIface.h"
namespace SGA {
	/*
	��Ʋ�� �̹��� _imageSource���� ��������Ʈ ������ ��Ÿ���� Ŭ����.
	*/
	class Sprite : public SpriteIface
	{
		struct tagClippingInfo {
			int clipPosX, clipPosY;
			int pivotX, pivotY;
			int w, h;
		};
	public:
		Sprite(const BitmapImage* imgSrc,
			const TCHAR* spriteName,
			int clipPosX, int clipPosY,
			int clipWidth, int clipHeight,
			float px, float py);

		virtual ~Sprite();

		/*
		��������Ʈ�� pivotPoint�� drawPos�� ��ġ�ϵ��� �׸���.
		*/
		virtual void render(HDC hdc, int drawPosX, int drawPosY) const;

		inline const TCHAR* getName() const {
			return _spriteName;
		}

		inline int getWidth() const {
			return _clip.w;
		}

		inline int getHeight() const {
			return _clip.h;
		}
	private:
		//��Ʋ�� �̹����������� ��ġ�� ũ��
		tagClippingInfo _clip;

		//��������Ʈ �̸�
		const TCHAR* _spriteName;
		const BitmapImage* _imageSource;
	};
}