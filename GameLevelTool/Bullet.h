#pragma once
#include "GameObject.h"
#include <Windows.h>
#include <SpritesAnimation.h>
#include "BulletController.h"
namespace SGA {
	enum BulletTypes {
		BULLET_TYPE_PROJECTILE,
		BULLET_TYPE_FLAME,
		BULLET_TYPE_EXPLOSIVE,
		BULLET_TYPE_BOMB
	};

	enum BulletOnwers {
		BULLET_OWNER_IS_PLAYER,
		BULLET_OWENR_IS_ENEMY
	};

	class Bullet : public GameObject
	{
	public:
		Bullet(BulletTypes bulletType, BulletCtrlIface * bulletCtrl, BulletOnwers owner,
			POINTFLOAT position, int damage, SpritesAnimation * flyingAni, SpritesAnimation * hitAni,
			RECT collisionRECT, CollisionTypes collisionType, bool destructable, int HP);

		~Bullet();

		Bullet* clone();

		void update();

		void render();

		GameObjectTypes getTypeID() const {
			return GAME_OBJECT_BULLET;
		}

		BulletTypes getBulletTypeID() const {
			return _bulletType;
		}

		const RECT& getCollisionRect() const {
			return _collisionRECT;
		}

		const CollisionTypes getCollisionType() const {
			return _collisionType;
		}

		void onCollision(GameObject* other);

		BulletOnwers getOwner() const {
			return _owner;
		}

		bool isDestructable() const {
			return _destructable;
		}

		bool isDestroied() const {
			return _destroied;
		}

		void killedBy(Bullet* bullet);
		void killedBy(EnemyObject* bullet);
		void killedBy(PlayerObject * bullet);
	private:
		void setHitted();
	private:
		POINTFLOAT _firedPos;
		SpritesAnimation* _animationFlying;
		SpritesAnimation* _animationHit;
		RECT _collisionRECT;
		CollisionTypes _collisionType;
		BulletOnwers _owner;
		BulletCtrlIface* _bulletCtrl;
		int _damage;
		bool _destructable;
		BulletTypes _bulletType;
		bool _hitted;
		bool _destroied;
	};
}
