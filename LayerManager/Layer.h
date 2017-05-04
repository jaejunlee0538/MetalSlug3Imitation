#pragma once
#include <BitmapImage.h>
namespace SGA {
	class SpriteIface;
	class Layer{
	public:
		/*
		width : ���̾��� ���� �ȼ� ����
		height : ���̾��� ���� �ȼ� ����
		bkColor : clearLayerȣ�� �� bkColor�� ���̾ clear�ȴ�.
		enableTransparent : true�� �����ϸ� ȭ�鿡 ������ �� �� bkColor���� ����ó���Ͽ� �������Ѵ�.
		*/
		Layer(int width, int height, COLORREF bkColor, bool enableTransparent);

		/*
		*/
		virtual ~Layer();

		/*
		*/
		void resize(int width, int height);

		/*
		���̾� ĵ������ �׷��� �׸��� hdc�� �Ű� �׸���.
		*/
		void renderThisLayer(HDC hdc);

		/*
		���̾� ��ü�� bkColor������ ĥ�Ѵ�.
		*/
		void clearLayer();

		/*
		sprite�� World�� (x,y) ��ǥ�� �������Ѵ�.
		ȭ�� ���� sprite�� ���������� �ʴ´�.
		*/
		virtual void renderInWrold(const SpriteIface* sprite, float x, float y);
		/*
		sprite�� ȭ���� (x,y)��ǥ�� �������Ѵ�.
		*/
		virtual void renderOnScreen(const SpriteIface* sprite, int x, int y);
	private:
		BitmapImage _canvas;
		COLORREF _bkColor;
	};
}