#pragma once
#include "BitmapImage.h"

namespace SGA {
	class SpriteIface;
	class Camera;
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

		HDC getDC();

		/*
		sprite�� World�� (x,y) ��ǥ�� �������Ѵ�.
		ȭ�� ���� sprite�� ���������� �ʴ´�.
		*/
		virtual void renderInWrold(const SpriteIface* sprite, float x, float y);
		/*
		sprite�� ȭ���� (x,y)��ǥ�� �������Ѵ�.
		*/
		virtual void renderOnScreen(const SpriteIface* sprite, int x, int y);

		virtual void drawRectangleInWorld(float x, float y, int w, int h);

		virtual void drawCircleInWorld(float x, float y, int R);

		virtual void drawPolygon(const POINT* pts, int n);
		virtual void drawPolygon(const POINTFLOAT* pts, int n);
	private:
		BitmapImage _canvas;
		COLORREF _bkColor;
		const Camera* _camera;
	};
}