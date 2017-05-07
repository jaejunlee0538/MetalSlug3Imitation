#include "Enemy.h"
#include <CommonMacroHeader.h>
#include "Stdafx.h"
#include <CollisionComponentRectangle.h>
#include <LayerManager.h>
#include <BulletIface.h>
#include "Player.h"
namespace SGA {
	Enemy::Enemy(std::string tag, int hp, int width, int height, int alertRangeRadius)
		: _tag(tag), _hp(hp)
	{
		_groundCheckTrigger = new CollisionTriggerBox(0, height / 2, width / 2, 3, "EnemyGNDCheck");

		_footCircle = new WalkerFootCircle(0, height / 2 - width / 2, width/2);
		
		_bodyCollision = new CollisionComponentRectangle(*this,
			SGA::makeRectCenter<RECT, int>(0, 0, width, height), false, COLLISION_LAYER_ENEMY_BODY);

	/*	_leftCloseAttackTrigger = new CollisionTriggerBox(-width / 2, 0, 30 + width / 2, height / 2, "LeftCloseAttack");
		_rightCloseAttackTrigger = new CollisionTriggerBox(width / 2, 0, 30 + width / 2, height / 2, "RightCloseAttack");
		addChild(_leftCloseAttackTrigger);
		addChild(_rightCloseAttackTrigger);*/
		_leftCloseAttackTrigger = NULL;
		_rightCloseAttackTrigger = NULL;

		setCollisionComponent(_bodyCollision);
		addChild(_footCircle);
		addChild(_groundCheckTrigger);

		_renderLayer = GET_LAYER_MANAGER()->findLayer(SGA::LayerManager::LAYER_INDEX_GAME_OBJECT);
	}

	Enemy::~Enemy()
	{

	}

	void Enemy::enableCloseAttack(int width, int height)
	{
		_leftCloseAttackTrigger = new CollisionTriggerBox(-width /2, 0, width, height, "LeftCloseAttack");
		_rightCloseAttackTrigger = new CollisionTriggerBox(width / 2, 0, width, height, "RightCloseAttack");
		addChild(_leftCloseAttackTrigger);
		addChild(_rightCloseAttackTrigger);
	}

	void Enemy::onCollidingEnter(GameObject & other)
	{
		if (other.getTag() == "PlayerBullet") {
			attacked();
			BulletIface* bullet = dynamic_cast<BulletIface*>(&other);
			assert(bullet != NULL);
			giveDamage(bullet->getDamage());
			if (getCurrentHP() == 0) {
				Player* player = dynamic_cast<Player*>(bullet->getShooter());
				assert(player != NULL);
				diedByBullet(*player, *bullet);
			}
		}	
	}

	void Enemy::onTrigerring(GameObject & other)
	{
		if (other.getTag() == "LeftJumpTrigger") {
			onStayJumpTrigger(true);
		}
		else if (other.getTag() == "RightJumpTrigger") {
			onStayJumpTrigger(false);
		}else if(other.getTag() == "PlayerCloseAttackBox") {
			attacked();
			Player* player = dynamic_cast<Player*>(other.getParent());
			assert(player != NULL);
			giveDamage(player->getCloseAttackDamage());
			if (getCurrentHP() == 0) {
				diedByKnife(*player);
			}
		}
	}

	bool Enemy::isGrounded() const
	{
		return _groundCheckTrigger->isCollisionTriggered();
	}
	
	void Enemy::giveDamage(int damage) {
		_hp -= damage;
		if (_hp < 0) {
			_hp = 0;
		}
	}
}