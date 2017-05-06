#include "Camera.h"
#include "CommonMacroHeader.h"
namespace SGA {


	Camera::Camera()
	{
		disableGravity();
		enableKinematic();
		_target = NULL;
	}


	Camera::~Camera()
	{
	}

	void Camera::transformWorldToScreen(float & x, float & y) const
	{
		x -= getPosition().x;
		y -= getPosition().y;
		x += _width / 2;
		y += _height / 2;
	}

	RECT Camera::getScreenRECT() const {
		POINTFLOAT pos = getPosition();
		return SGA::makeRectCenter<RECT, int>(pos.x, pos.y, _width, _height);
	}

	
}