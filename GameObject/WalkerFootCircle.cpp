#include "WalkerFootCircle.h"
#include "CollisionComponentCircle.h"
#include "CommonMacroHeader.h"
//#include "Stdafx.h"
#include "LayerManager.h"
#include "CollisionConfig.h"
#include "Global.h"
#include "KeyManager.h"
namespace SGA {
	WalkerFootCircle::WalkerFootCircle(int posX, int posY, int radius)
		:_R(radius)
	{
		disableGravity();
		//disableKinamatic();
		setPosition(posX, posY);
		CollisionComponentCircle* footCircle
			= new CollisionComponentCircle(*this, 
				SGA::makeRectCenter<RECT, int>(0, 0, 2*radius, 2*radius), 
				false, COLLISION_LAYER_PLAYER_BODY);
		setCollisionComponent(footCircle);
	}


	WalkerFootCircle::~WalkerFootCircle()
	{

	}
	
	bool WalkerFootCircle::isRenderable() const {
#if DEBUG_ENABLE_DRAW_PLAYER_HIDDEN_COMPONENT
		return GET_KEY_MANAGER()->isToggleKey('1');
#else
		return false;
#endif
	}

	void WalkerFootCircle::render()
	{
#if DEBUG_ENABLE_DRAW_PLAYER_HIDDEN_COMPONENT
		Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_FOREGROUND);
		layer->drawCircleInWorld(getPosition().x, getPosition().y, _R);
#endif
	}
}