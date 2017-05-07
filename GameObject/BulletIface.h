#pragma once
#include "GameObject.h"
namespace SGA {
	class BulletIface : public GameObject
	{
	public:
		BulletIface() {

		}

		virtual ~BulletIface() {

		}

		bool isRenderable() const {
			return true;
		}

		virtual GameObject* getShooter() = 0;

		virtual int getDamage() const = 0;
	};

}