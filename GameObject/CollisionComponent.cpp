#include "CollisionComponent.h"
#include "GameObject.h"
namespace SGA {
	CollisionComponent::CollisionComponent(GameObject & owner, bool isTrigger, uint8_t collisionMask)
		:_owner(owner), _isTrigger(isTrigger), _collisionMask(collisionMask)
	{
		setOffset(0, 0);
	}
	void CollisionComponent::setOffset(float offsetX, float offsetY) {
		_offset.x = offsetX;
		_offset.y = offsetY;
	}
	void CollisionComponent::handleCollision(CollisionComponent * other) {
		if (_collisionMemory.find(other) == _collisionMemory.end()) {
			_collisionMemory.insert(other);
			if (other->isTrigger()) {
				_owner.onTrigerringEnter(other->getOwner());
			}
			else {
				_owner.onCollidingEnter(other->getOwner());
			}
		}
		if (other->isTrigger()) {
			_owner.onTrigerring(other->getOwner());
		}
		else {
			_owner.onColliding(other->getOwner());
		}
	}
	void CollisionComponent::handleNoneCollision(CollisionComponent * other) {
		if (_collisionMemory.find(other) != _collisionMemory.end()) {
			_collisionMemory.erase(other);
			if (other->isTrigger()) {
				_owner.onTrigerringExit(other->getOwner());
			}
			else {
				_owner.onCollidingExit(other->getOwner());
			}
		}
	}
}