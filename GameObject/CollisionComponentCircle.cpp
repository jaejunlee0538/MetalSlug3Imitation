#include "CollisionComponentCircle.h"
#include "CollisionComponentRectangle.h"
#include "CollisionComponentRectangleRotated.h"
#include "GameObject.h"

namespace SGA {
	CollisionComponentCircle::CollisionComponentCircle(GameObject & owner, RECT circle, bool isTrigger, CollisionLayers collisionLayer)
		:CollisionComponent(owner, isTrigger, collisionLayer) {
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

	bool CollisionComponentCircle::implCollisionCheck(const CollisionComponentRectangleRotated * other) const
	{
		RECT myCircle = getCollisionRECT();
		return SGA::isCollideCircleRotatedRect(myCircle, other->getUnrotatedRECT(), other->getAngle());
	}

	void CollisionComponentCircle::resolveCollisionWith(CollisionComponent * other) const
	{
		other->resolveCollisionBy(this);
	}

	void CollisionComponentCircle::resolveCollisionBy(const CollisionComponentRectangle * other)
	{
		RECT myCircle = getCollisionRECT();
		RECT otherRect = other->getCollisionRECT();
		POINTFLOAT vec = SGA::getCollisionVectorCircleRect<RECT, POINTFLOAT>(myCircle, otherRect);
		//getOwner().movePosition(vec.x, vec.y);
		moveCollidingObject(&getOwner(), vec.x, vec.y);
	}

	void CollisionComponentCircle::resolveCollisionBy(const CollisionComponentCircle * other)
	{
		RECT myCircle = getCollisionRECT();
		RECT otherCircle = other->getCollisionRECT();
		POINTFLOAT vec = SGA::getCollisionVectorCircleCircle<RECT, POINTFLOAT>(myCircle, otherCircle);
		//getOwner().movePosition(vec.x, vec.y);
		moveCollidingObject(&getOwner(), vec.x, vec.y);
	}

	void CollisionComponentCircle::resolveCollisionBy(const CollisionComponentRectangleRotated * other)
	{
		POINTFLOAT vec = SGA::getCollisionVectorCircleRotatedRect<RECT, POINTFLOAT>(getCollisionRECT(), other->getUnrotatedRECT(), other->getAngle());
		moveCollidingObject(&getOwner(), vec.x, vec.y);
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