#include "CollisionComponentRectangle.h"
#include "CollisionComponentCircle.h"
#include "GameObject.h"

namespace SGA {
	CollisionComponentRectangle::CollisionComponentRectangle(GameObject& owner, RECT rect, bool isTrigger, uint8_t collisionMask)
		:CollisionComponent(owner, isTrigger, collisionMask) {
		setRECT(rect);
	}

	bool CollisionComponentRectangle::isCollideWith(const CollisionComponent * other) const {
		return other->implCollisionCheck(this);
	}

	bool CollisionComponentRectangle::implCollisionCheck(const CollisionComponentRectangle * other)const
	{
		RECT myRect = getCollisionRECT();
		RECT otherRect = other->getCollisionRECT();
		return SGA::isCollideRectRect(myRect, otherRect);
	}
	bool CollisionComponentRectangle::implCollisionCheck(const CollisionComponentCircle * other)const
	{
		RECT rect = getCollisionRECT();
		RECT circle = other->getCollisionRECT();
		return SGA::isCollideRectCircle(rect, circle);
	}

	RECT CollisionComponentRectangle::getCollisionRECT() const
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