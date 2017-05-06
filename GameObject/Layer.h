#pragma once
#include "BitmapImage.h"

namespace SGA {
	class SpriteIface;
	class Camera;
	class Layer{
	public:
		/*
		width : 레이어의 가로 픽셀 개수
		height : 레이어의 세로 픽셀 개수
		bkColor : clearLayer호출 시 bkColor로 레이어가 clear된다.
		enableTransparent : true로 설정하면 화면에 렌더링 할 때 bkColor색을 투명처리하여 렌더링한다.
		*/
		Layer(int width, int height, COLORREF bkColor, bool enableTransparent);

		/*
		*/
		virtual ~Layer();

		/*
		*/
		void resize(int width, int height);

		/*
		레이어 캔버스에 그려진 그림을 hdc에 옮겨 그린다.
		*/
		void renderThisLayer(HDC hdc);

		/*
		레이어 전체를 bkColor색으로 칠한다.
		*/
		void clearLayer();

		HDC getDC();

		/*
		sprite를 World의 (x,y) 좌표에 렌더링한다.
		화면 밖의 sprite는 렌더링되지 않는다.
		*/
		virtual void renderInWrold(const SpriteIface* sprite, float x, float y);
		/*
		sprite를 화면의 (x,y)좌표에 렌더링한다.
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