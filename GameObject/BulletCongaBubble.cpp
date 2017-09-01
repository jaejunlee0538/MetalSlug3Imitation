#include "BulletCongaBubble.h"
#include "CollisionConfig.h"
#include "WorldClock.h"
#include "AnimationManager.h"
namespace SGA {
	BulletCongaBubble::BulletCongaBubble()
		:BulletIface(COLLISION_LAYER_ENEMY_BULLET)
	{
		setTargetObjectTypes({ GameObjectTypes::GROUND, GameObjectTypes::PLAYER , GameObjectTypes::STRUCTURE});
		setBulletRadius(8);
		_animFlying = GET_ANIMATION_MANAGER()->findAnimation("Enemy_Conga_Bubble_Fly");
		_animFlying = GET_ANIMATION_MANAGER()->findAnimation("Enemy_Conga_Bubble_Fly");

	}


	BulletCongaBubble::~BulletCongaBubble()
	{
	}

	void BulletCongaBubble::bulletMotionUpdate()
	{
		movePosition(2, sin(GET_GAME_WORLD_CLOCK()->getCurrentTimeMillis()*0.001));
	}

	void BulletCongaBubble::onHitTarget(GameObject & other)
	{

	}

	void BulletCongaBubble::onDestroied()
	{

	}
}