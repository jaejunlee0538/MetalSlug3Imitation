#include "Bullet.h"
#include "LayerManager.h"
#include <assert.h>
namespace SGA {
	Bullet::Bullet(BulletTypes bulletType, BulletCtrlIface * bulletCtrl, BulletOnwers owner,
		POINTFLOAT position, int damage, SpritesAnimation * flyingAni, SpritesAnimation * hitAni, 
		RECT collisionRECT, CollisionTypes collisionType, bool destructable, int HP)
		:_bulletType(bulletType), _bulletCtrl(bulletCtrl), _owner(owner), _damage(damage),
		_destructable(destructable), _animationFlying(flyingAni), _animationHit(hitAni),
		_collisionRECT(collisionRECT),_collisionType(collisionType)
	{
		setHP(HP);
		setPosition(position.x, position.y);
		_destroied = false;
	}


	Bullet::~Bullet()
	{
		delete _animationFlying;
		delete _animationHit;
		delete _bulletCtrl;
	}

	Bullet * Bullet::clone()
	{
		Bullet * bullet = new Bullet(_bulletType, _bulletCtrl->clone(),
			_owner, getPosition(), _damage, 
			_animationFlying->clone(), _animationHit->clone(), 
			_collisionRECT, _collisionType, _destructable, getHP());
	}

	void Bullet::update() {
		if (_hitted) {
			if (_animationHit->getPlayCount() == 0) {
				_destroied = true;
			}
		}
	}

	void Bullet::render() {
		assert(isDestroied());
		if (_hitted) {
			_layer->renderInWrold(_animationHit, getPosition().x, getPosition().y);
		}
		else {
			_layer->renderInWrold(_animationFlying, getPosition().x, getPosition().y);
		}
	}
	
	void Bullet::onCollision(GameObject * other) {
		if (getOwner()==BULLET_OWNER_IS_PLAYER) {
			switch (other->getTypeID()) {
			case GAME_OBJECT_ENEMY:					//플레이어 총알 VS Enemy
			case GAME_OBJECT_DESTRUCTABLE_STRUCTURE://플레이어 총알 VS 파괴가능 구조물
			{
				other->setHP(other->getHP() - _damage);
				if (other->getHP() == 0) {
					other->killedBy(this);
				}
			}
				break;
			case GAME_OBJECT_BULLET:				
			{
				Bullet* otherBullet = dynamic_cast<Bullet*>(other);
				if (otherBullet->getOwner() != BULLET_OWNER_IS_PLAYER) {//플레이어 총알 vS 적 총알
					if (other->isDestructable()) {
						other->setHP(other->getHP() - _damage);
						if (other->getHP() == 0) {
							other->killedBy(this);
						}
					}
				}
			}
				break;
			}
		}
		else {
			switch (other->getTypeID()) {
			case GAME_OBJECT_PLAYER:{//적 총알 VS 플레이어
				other->killedBy(this);
				setHitted();
			}
			break;
			}
		}
	}

	void Bullet::killedBy(Bullet * bullet)
	{
		setHitted();
	}

	void Bullet::killedBy(EnemyObject * bullet)
	{
		setHitted();
	}

	void Bullet::killedBy(PlayerObject * bullet)
	{
		setHitted();
	}

	void Bullet::setHitted()
	{
		_hitted = true;
	}
}