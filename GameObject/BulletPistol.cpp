#include "BulletPistol.h"
#include "CollisionConfig.h"
#include "AnimationManager.h"
#include "WorldClock.h"
namespace SGA {


	BulletPistol::BulletPistol()
		:BulletIface(COLLISION_LAYER_PLAYER_BULLET)
	{
		setUnlockedToParent();
		setTargetObjectTypes({ GameObjectTypes::ENEMY, GameObjectTypes::GROUND, GameObjectTypes::STRUCTURE });
		setBulletRadius(6);
		_animPistolFly = GET_ANIMATION_MANAGER()->findAnimation("Bullet_Pistol_Fly_Left");
		_animPistolDestroyA = GET_ANIMATION_MANAGER()->findAnimation("Bullet_Pistol_DestroyA_Left");
	}

	BulletPistol::~BulletPistol()
	{

	}

	void BulletPistol::setVelocity(float vx, float vy)
	{
		_vx = vx;
		_vy = vy;
	}

	void BulletPistol::onFire()
	{
		_animPistolFly->restart();
		setCurrentAnimation(_animPistolFly);
	}

	void BulletPistol::bulletMotionUpdate()
	{
		float dt = GET_GAME_WORLD_CLOCK()->getDeltaTimeMillis()*0.001f;
		movePosition(_vx*dt, _vy*dt);
	}

	void BulletPistol::onHitTarget(GameObject & other)
	{
		destroy();
	}

	void BulletPistol::onDestroied()
	{
		_animPistolDestroyA->restart();
		setCurrentAnimation(_animPistolDestroyA);
	}
}