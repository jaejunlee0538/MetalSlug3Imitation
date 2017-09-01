#pragma once
#include "BulletIface.h"
namespace SGA {
	class BulletCongaBubble :
		public BulletIface
	{
	public:
		BulletCongaBubble();
		virtual ~BulletCongaBubble();

		virtual void bulletMotionUpdate();
		virtual void onHitTarget(GameObject& other);
		virtual void onDestroied();
	private:
		SpritesAnimation* _animFlying;
		SpritesAnimation* _animDestroy;
	};

}