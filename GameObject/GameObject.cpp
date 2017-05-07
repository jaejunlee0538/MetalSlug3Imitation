#include "GameObject.h"

namespace SGA {
	GameObject::GameObject()
	{
		setPosition(0, 0);
		setActive();
		enableGravity();
		disableKinamatic();
	}

	GameObject::~GameObject()
	{
		if (_collisionComponent) {
			delete _collisionComponent;
		}
		for (auto it = _childs.begin(); it != _childs.end(); ++it) {
			delete *it;
		}
	}


	//////////////////////////////////////////////////////////////

	GameObject * GameObject::getParent() {
		return _parent;
	}

	void GameObject::addChild(GameObject * child) {
		_childs.push_back(child);
		child->_parent = this;
	}

	CollisionComponent * GameObject::setCollisionComponent(CollisionComponent * collisionComponent) {
		CollisionComponent* old = _collisionComponent;
		_collisionComponent = collisionComponent;
		return old;
	}

	///////////////////////////////////////////////////////////////////
	void GameObject::movePosition(float dx, float dy)
	{
		setPosition(_position.x+dx, _position.y+dy);
	}

	void GameObject::setPosition(float x, float y) {
		_deltaPos.x = x - _position.x;
		_deltaPos.y = y - _position.y;

		_position.x = x;
		_position.y = y;
	}

	POINTFLOAT GameObject::getPosition() const {
		POINTFLOAT pos = _position;
		if (_parent) {
			POINTFLOAT parentPos = _parent->getPosition();
			pos.x += parentPos.x;
			pos.y += parentPos.y;
		}
		return pos;
	}

	POINTFLOAT GameObject::getDeltaPosition() const
	{
		if (_parent) {
			return _parent->getDeltaPosition();
		}
		return _deltaPos;
	}

	void GameObject::beginCollisionCheck()
	{
		if (_collisionComponent) {
			_collisionComponent->beginCollisionCheck();
		}
		for (auto it = _childs.begin(); it != _childs.end(); ++it) {
			(*it)->beginCollisionCheck();
		}
	}

	void GameObject::endCollisionCheck()
	{
		if (_collisionComponent) {
			_collisionComponent->endCollisionCheck();
		}
		for (auto it = _childs.begin(); it != _childs.end(); ++it) {
			(*it)->endCollisionCheck();
		}
	}

	void GameObject::checkCollisionWith(GameObject * other)
	{
		__collisionCheckInternal(other, true);
	}

	void GameObject::__resolveCollision(GameObject * other)
	{
		uint8_t test = this->isKinematic() ? 0x01 : 0x00;
		test |= other->isKinematic() ? 0x02 : 0x00;
		switch (test) {
		case 0x00:
		{
			//둘다 일반 Collider
			//collision1->resolveCollisionWith(collision2);
			//TODO : 이럴 때는 어떤 애를 움직여야지?
		}
		break;
		case 0x01:
		{
			//this가 kinematic
			_collisionComponent->resolveCollisionWith(other->getCollisionComponent());
		}
		break;
		case 0x02:
		{
			//other가 kinematic
			other->getCollisionComponent()->resolveCollisionWith(_collisionComponent);
		}
		break;
		case 0x03:
		{
			//둘다 Kinamatic
			//아무일도 하지 않음
		}
		break;
		}
	}
	void GameObject::__collisionCheckInternal(GameObject * other, bool ccc)
	{
		//check
		if (ccc) {
			//나와 other/other의 자식들과의 충돌 체크를 시도 한다.
			other->__collisionCheckInternal(this, false);
			for (auto it = _childs.begin(); it != _childs.end(); ++it) {
				//내 자식과 other/other의 자식들과의 충돌 체크를 시도한다.
				other->__collisionCheckInternal(*it, false);
			}
		}
		else {
			//collision check
			if (other->isCollidable()) {
				//other가 충돌이 가능한 오브젝트라면 
				if (this->isCollidable()) {
					//this가 충돌가능한 오브젝트라면 실제 충돌체크 수행
					CollisionComponent* otherCollision = other->getCollisionComponent();
					if (_collisionComponent->isCollidableWith(otherCollision)) {
						if (_collisionComponent->isCollideWith(otherCollision)) {
							_collisionComponent->handleCollision(_collisionComponent);
							otherCollision->handleCollision(_collisionComponent);
							__resolveCollision(other);
						}
					}
				}

				//this의 자식들이 충돌 가능한 오브젝트일 수 있으니 other와의 충돌 체크를 시도한다.
				for (auto it = _childs.begin(); it != _childs.end(); ++it) {
					(*it)->__collisionCheckInternal(other, false);
				}
			}
		}
	}
}