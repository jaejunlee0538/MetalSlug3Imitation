#include "Layer.h"
#include <assert.h>
namespace SGA {
	Layer::Layer(int width, int height)
	{
		resize(width, height);
	}

	Layer::~Layer()
	{

	}

	void Layer::resize(int width, int height)
	{
		assert(_canvas.init(width, height) == S_OK);
	}

	void Layer::renderInWrold(const Sprite * sprite, float x, float y)
	{

	}

	void Layer::renderOnScreen(const Sprite * sprite, int x, int y)
	{
		//sprite->render(_canvas.getDC(), )
	}
}