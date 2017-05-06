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

		SelectObject(_canvas.getDC(), GetStockObject(HOLLOW_BRUSH));
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
		Rectangle(_canvas.getDC(), x - w / 2, y - h / 2, x + w / 2, y + h / 2);
	}

	void Layer::drawCircleInWorld(float x, float y, int R)
	{
		_camera->transformWorldToScreen(x, y);
		Ellipse(_canvas.getDC(), x -  R, y - R, x + R, y + R);
	}

	void Layer::drawPolygon(const POINT * pts, int n)
	{
		Polygon(_canvas.getDC(), pts, n);
	}

	void Layer::drawPolygon(const POINTFLOAT* pts, int n)
	{
		POINT* p = new POINT[n+1];
		for (int i = 0; i < n; i++) {
			p[i].x = pts[i].x;
			p[i].x = pts[i].x;
		}
		p[n].x = pts[0].x;
		p[n].y = pts[0].y;

		drawPolygon( p, n+1);
		delete[] p;
	}
}