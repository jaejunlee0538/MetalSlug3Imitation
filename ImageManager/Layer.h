#pragma once
#include "Sprite.h"
#include "BitmapImage.h"
namespace SGA {
	class Sprite;
	class Layer{
	public:
		Layer(int width, int height);
		virtual ~Layer();
		void resize(int width, int height);
		virtual void renderInWrold(const Sprite* sprite, float x, float y);
		virtual void renderOnScreen(const Sprite* sprite, int x, int y);
	private:
		BitmapImage _canvas;
	};
}