#pragma once
#include "GameObject.h"
namespace SGA {
	class GroundRectangle : public GameObject
	{
	public:
		GroundRectangle(int posX, int posY, int width, int height);
		~GroundRectangle();

		std::string getTag() const {
			return "Ground";
		}
		void render();
		bool isRenderable() const;
	private:
		int _width, _height;
	};
}
