#pragma once
#include "BulletIface.h"
#include "SpritesAnimation.h"
namespace SGA {
	class BulletPistol :
		public BulletIface
	{
	public:
		BulletPistol();
		virtual ~BulletPistol();
		GameObjectTypes getTypeID() const {
			return GameObjectTypes::PLAYER_BULLET;
		}
		void setVelocity(float vx, float vy);
		virtual void onFire();
		virtual void bulletMotionUpdate();
		virtual void onHitTarget(GameObject& other);
		virtual void onDestroied();
	private:
		float _vx, _vy;
		SpritesAnimation* _animPistolFly;
		SpritesAnimation* _animPistolDestroyA;
	};
}