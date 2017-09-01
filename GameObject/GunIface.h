#pragma once
#include "GameObject.h"
namespace SGA {
	class GunIface : public GameObject
	{
	public:
		GunIface();
		virtual ~GunIface();
		virtual bool isRenderable() const {
			return false;
		}
		virtual void fire(float posX, float posY, int xDir, int yDir) = 0;
	};
}