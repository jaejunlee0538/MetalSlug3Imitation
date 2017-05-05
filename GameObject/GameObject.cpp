#include "GameObject.h"

namespace SGA {
	GameObject::GameObject()
	{
		setPosition(0, 0);
		setInactive();
		enableGravity();
		disableKinamatic();
	}

	GameObject::~GameObject()
	{

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
}