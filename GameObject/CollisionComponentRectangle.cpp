#include "CollisionComponentRectangle.h"
#include "CollisionComponentCircle.h"
#include "GameObject.h"

namespace SGA {
	CollisionComponentRectangle::CollisionComponentRectangle(GameObject& owner, RECT rect, bool isTrigger, CollisionLayers collisionLayer)
		:CollisionComponent(owner, isTrigger, collisionLayer) {
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

	bool CollisionComponentRectangle::implCollisionCheck(const CollisionComponentRectangleRotated * other) const
	{
		return false;
	}

	void CollisionComponentRectangle::resolveCollisionWith(CollisionComponent * other) const
	{
		other->resolveCollisionBy(this);
	}

	void CollisionComponentRectangle::resolveCollisionBy(const CollisionComponentRectangle * other)
	{
		RECT myRect = getCollisionRECT();
		RECT otherRect = other->getCollisionRECT();
		POINTFLOAT vec = SGA::getCollisionVectorRectRect<RECT, POINTFLOAT>(myRect, otherRect);
		POINTFLOAT vv = getOwner().getDeltaPosition();
		if (std::abs(getOwner().getDeltaPosition().x) < 0.01) {
			vec.x = 0;
		}
		if (std::abs(getOwner().getDeltaPosition().y) < 0.01) {
			vec.y = 0;
		}
		moveCollidingObject(&getOwner(), vec.x, vec.y);
		//getOwner().movePosition(vec.x, vec.y);
	}

	void CollisionComponentRectangle::resolveCollisionBy(const CollisionComponentCircle * other)
	{
		RECT myRect = getCollisionRECT();
		RECT otherCircle = other->getCollisionRECT();
		POINTFLOAT vecInv = SGA::getCollisionVectorCircleRect<RECT, POINTFLOAT>(otherCircle, myRect);
		moveCollidingObject(&getOwner(), -vecInv.x, -vecInv.y);
		//getOwner().movePosition(-vecInv.x, -vecInv.y);
	}

	void CollisionComponentRectangle::resolveCollisionBy(const CollisionComponentRectangleRotated * other)
	{

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