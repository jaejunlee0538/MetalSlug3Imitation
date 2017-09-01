#pragma once
#include "GunIface.h"
#include "BulletPistol.h"
namespace SGA {
	class GunPistol :
		public GunIface
	{
		enum {
			BULLET_MAX = 100
		};
	public:
		GunPistol();
		virtual ~GunPistol();
		void update();
		void fire(float posX, float posY, int xDir, int yDir);
	private:
		BulletPistol _bullet[BULLET_MAX];
	};
}