#include "Camera.h"
#include "GameObject.h"
namespace SGA {
	Camera::Camera(int width, int height)
		:_width(width), _height(height), _targetObject(NULL)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::update()
	{
		if (_targetObject) {
			setPosition(_targetObject->getPosition().x, _targetObject->getPosition().y);
		}
	}

	RECT Camera::getScreenRECT() const
	{
		RECT rect;
		rect.left = _position.x - _width / 2;
		rect.right = rect.left + _width;
		rect.top = _position.y - _height / 2;
		rect.bottom = rect.top + _height;
		return rect;
	}
}