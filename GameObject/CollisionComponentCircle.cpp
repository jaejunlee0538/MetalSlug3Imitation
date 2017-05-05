#include "CollisionComponentCircle.h"
#include "CollisionComponentRectangle.h"
#include "GameObject.h"

namespace SGA {
	CollisionComponentCircle::CollisionComponentCircle(GameObject & owner, RECT circle, bool isTrigger, uint8_t collisionMask)
		:CollisionComponent(owner, isTrigger, collisionMask) {
		setRECT(circle);
	}

	bool CollisionComponentCircle::isCollideWith(const CollisionComponent * other) const {
		return other->implCollisionCheck(this);
	}

	bool CollisionComponentCircle::implCollisionCheck(const CollisionComponentRectangle * other)const
	{
		RECT circle = getCollisionRECT();
		RECT rect = other->getCollisionRECT();
		return SGA::isCollideRectCircle(rect, circle);
	}

	bool CollisionComponentCircle::implCollisionCheck(const CollisionComponentCircle * other)const
	{
		RECT myCircle = getCollisionRECT();
		RECT otherCircle = other->getCollisionRECT();
		return SGA::isCollideCircleCircle(myCircle, otherCircle);
	}

	RECT CollisionComponentCircle::getCollisionRECT() const
	{
		RECT collisionRect;
		POINTFLOAT ownerPos = _owner.getPosition();
		collisionRect.left = _rect.left + ownerPos.x + _offset.x;
		collisionRect.right = _rect.right + ownerPos.x + _offset.x;
		collisionRect.top = _rect.top + ownerPos.y + _offset.y;
		collisionRect.bottom = _rect.bottom + ownerPos.y + _offset.y;
		return collisionRect;
	}
}