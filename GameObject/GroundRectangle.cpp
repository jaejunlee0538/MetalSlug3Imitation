#include "GroundRectangle.h"
#include "CollisionComponentRectangle.h"
#include "CommonMacroHeader.h"
#include "CollisionConfig.h"
#include "LayerManager.h"
#include "Global.h"
#include "KeyManager.h"
namespace SGA {
	GroundRectangle::GroundRectangle(int posX, int posY, int width, int height)
		:_width(width), _height(height)
	{
		disableGravity();
		enableKinematic();
		setPosition(posX, posY);
		CollisionComponentRectangle * rectangle = new CollisionComponentRectangle(
			*this, SGA::makeRectCenter<RECT, int>(0, 0, width, height),
			false, COLLISION_LAYER_GROUND);
		setCollisionComponent(rectangle);
	}

	GroundRectangle::~GroundRectangle()
	{
	}
	
	void GroundRectangle::render()
	{
#if DEBUG_ENABLE_DRAW_GROUND
		Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_FOREGROUND);
		layer->drawRectangleInWorld(getPosition().x, getPosition().y, _width, _height);
#endif
	}

	bool GroundRectangle::isRenderable() const {
#if DEBUG_ENABLE_DRAW_GROUND
		return GET_KEY_MANAGER()->isToggleKey('3');
#else
		return false;
#endif
	}
}