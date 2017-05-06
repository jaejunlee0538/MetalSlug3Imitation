#include "Layer.h"
#include <assert.h>
#include "SpriteIface.h"
#include "Camera.h"
namespace SGA {
	Layer::Layer(int width, int height, COLORREF bkColor, bool enableTransparent)
	{
		resize(width, height);
		_canvas.enableTransparent(enableTransparent);
		if (enableTransparent) {
			_canvas.setTransparentColor(bkColor);
		}
		_bkColor = bkColor;
		_camera = GET_CAMERA();
	}

	Layer::~Layer()
	{

	}

	void Layer::resize(int width, int height)
	{
		assert(_canvas.init(width, height) == S_OK);
		
	}

	void Layer::renderThisLayer(HDC hdc)
	{
		_canvas.render(hdc, 0, 0);
	}

	void Layer::clearLayer()
	{
		_canvas.clearImage(_bkColor);
	}

	HDC Layer::getDC()
	{
		return _canvas.getDC();
	}

	void Layer::renderInWrold(const SpriteIface * sprite, float x, float y)
	{
		POINTFLOAT camPos = _camera->getPosition();
		float xScreen = _camera->getCameraWidth() / 2.0f + x - camPos.x; //-_camera->getCameraWidth() / 2.0f;
		float yScreen = _camera->getCameraHeight() / 2.0f + y - camPos.y; //-_camera->getCameraHeight() / 2.0f;
		renderOnScreen(sprite, xScreen, yScreen);
	}

	void Layer::renderOnScreen(const SpriteIface * sprite, int x, int y)
	{
		sprite->render(_canvas.getDC(), x, y);
	}

	void Layer::drawRectangleInWorld(float x, float y, int w, int h)
	{
		_camera->transformWorldToScreen(x, y);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(_canvas.getDC(), GetStockObject(HOLLOW_BRUSH));
		Rectangle(_canvas.getDC(), x - w / 2, y - h / 2, x + w / 2, y + h / 2);
		//SelectObject(_canvas.getDC(), oldBrush);
	}

	void Layer::drawCircleInWorld(float x, float y, int R)
	{
		_camera->transformWorldToScreen(x, y);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(_canvas.getDC(), GetStockObject(HOLLOW_BRUSH));
		Ellipse(_canvas.getDC(), x -  R, y - R, x + R, y + R);
		//SelectObject(_canvas.getDC(), oldBrush);
	}

	void Layer::drawPolygonInWorld(const POINTFLOAT* pts, int n)
	{
		POINT* p = new POINT[n];
		float x, y;
		for (int i = 0; i < n; i++) {
			x = pts[i].x;
			y = pts[i].y;
			_camera->transformWorldToScreen(x, y);
			p[i].x = x;
			p[i].y = y;
		}
		//HBRUSH oldBrush = (HBRUSH)SelectObject(_canvas.getDC(), GetStockObject(HOLLOW_BRUSH));
		Polygon(_canvas.getDC(), p, n);
		//SelectObject(_canvas.getDC(), oldBrush);
		delete[] p;
	}
}