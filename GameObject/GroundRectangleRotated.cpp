#include "GroundRectangleRotated.h"
#include "CommonMacroHeader.h"
#include "CollisionConfig.h"
#include "LayerManager.h"
#include "Global.h"
#include "MathUtils.h"
namespace SGA {
	GroundRectangleRotated::GroundRectangleRotated(int posX, int posY, float angle, int width, int height)
		:_width(width), _height(height), _angle(angle)
	{
		disableGravity();
		enableKinematic();
		setPosition(posX, posY);
		_collision = new CollisionComponentRectangleRotated(
			*this, SGA::makeRectCenter<RECT, int>(0, 0, width, height), angle,
			false, COLLISION_LAYER_GROUND);
		setCollisionComponent(_collision);
	}

	GroundRectangleRotated::~GroundRectangleRotated()
	{
	}

	void GroundRectangleRotated::render()
	{
#if DEBUG_ENABLE_DRAW_GROUND
		Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_FOREGROUND);
		POINTFLOAT vertex[4];
		SGA::getRotatedRECT(_collision->getUnrotatedRECT(), getAngle(), vertex);
		layer->drawPolygonInWorld(vertex, 4);
#endif
	}

	bool GroundRectangleRotated::isRenderable() const {
#if DEBUG_ENABLE_DRAW_GROUND
		return true;
#else
		return false;
#endif
	}
	void GroundRectangleRotated::rotate(float dAngle) {
		setAngle(_angle + dAngle);
	}
	void GroundRectangleRotated::setAngle(float angle) {
		_angle = angle;
		_collision->setAngle(_angle);
	}
	float GroundRectangleRotated::getAngle() const {
		return _angle;
	}
	void GroundRectangleRotated::setWidth(int w) {
		_width = w;
		_collision->setRECT(SGA::makeRectCenter<RECT, int>(0, 0, _width, _height));
	}
	int GroundRectangleRotated::getWidth() const {
		return _width;
	}
	void GroundRectangleRotated::setHeight(int h) {
		_height = h;
		_collision->setRECT(SGA::makeRectCenter<RECT, int>(0, 0, _width, _height));
	}
	int GroundRectangleRotated::getHeight() {
		return _height;
	}
}