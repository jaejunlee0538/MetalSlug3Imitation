#include "Layer.h"
#include <assert.h>
#include <SpriteIface.h>
namespace SGA {
	Layer::Layer(int width, int height, COLORREF bkColor, bool enableTransparent)
	{
		resize(width, height);
		_canvas.enableTransparent(enableTransparent);
		if (enableTransparent) {
			_canvas.setTransparentColor(bkColor);
		}
		_bkColor = bkColor;
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

	void Layer::renderInWrold(const SpriteIface * sprite, float x, float y)
	{
		
	}

	void Layer::renderOnScreen(const SpriteIface * sprite, int x, int y)
	{
		sprite->render(_canvas.getDC(), x, y);
	}
}