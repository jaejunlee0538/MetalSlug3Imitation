#pragma once
#include "GameObject.h"
#include "CollisionComponentRectangleRotated.h"
namespace SGA {
	class GroundRectangleRotated : public GameObject
	{
	public:
		GroundRectangleRotated(int posX, int posY, float angle, int width, int height);
		~GroundRectangleRotated();

		std::string getTag() const {
			return "Ground";
		}
		void render();
		bool isRenderable() const;
		void rotate(float dAngle);
		void setAngle(float angle);
		float getAngle() const;
		void setWidth(int w);
		int getWidth() const;
		void setHeight(int h);
		int getHeight();
	private:
		CollisionComponentRectangleRotated * _collision;
		int _width, _height;
		float _angle;
	};
}
