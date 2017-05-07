#include "CollisionComponentRectangleRotated.h"
#include "CollisionCheckFunc.h"
#include "CollisionComponentCircle.h"
#include "CollisionComponentRectangle.h"
#include "GameObject.h"
namespace SGA {


	CollisionComponentRectangleRotated::CollisionComponentRectangleRotated(GameObject & owner, RECT rect, float angleRad, bool isTrigger, CollisionLayers collisionLayer)
		:CollisionComponent(owner, isTrigger, collisionLayer)
	{
		setRECT(rect);
		setAngle(angleRad);
	}

	CollisionComponentRectangleRotated::~CollisionComponentRectangleRotated()
	{

	}

	bool CollisionComponentRectangleRotated::isCollideWith(const CollisionComponent * other) const
	{
		return other->implCollisionCheck(this);
	}

	bool CollisionComponentRectangleRotated::implCollisionCheck(const CollisionComponentRectangle * other) const
	{
		return SGA::isCollideRotatedRectRotatedRect(other->getCollisionRECT(), 0.0f, getUnrotatedRECT(), getAngle());
	}

	bool CollisionComponentRectangleRotated::implCollisionCheck(const CollisionComponentCircle * other) const
	{
		RECT otherCircle = other->getCollisionRECT();
		return SGA::isCollideCircleRotatedRect(otherCircle, getUnrotatedRECT(), getAngle());
	}

	bool CollisionComponentRectangleRotated::implCollisionCheck(const CollisionComponentRectangleRotated * other) const
	{
		return SGA::isCollideRotatedRectRotatedRect(getUnrotatedRECT(), getAngle(), other->getUnrotatedRECT(), other->getAngle());
	}

	void CollisionComponentRectangleRotated::resolveCollisionWith(CollisionComponent * other) const
	{
		other->resolveCollisionBy(this);
	}

	void CollisionComponentRectangleRotated::resolveCollisionBy(const CollisionComponentRectangle * other)
	{
		//TODO
	}

	void CollisionComponentRectangleRotated::resolveCollisionBy(const CollisionComponentCircle * other)
	{
		POINTFLOAT vec = SGA::getCollisionVectorCircleRotatedRect<RECT, POINTFLOAT>(other->getCollisionRECT(), getUnrotatedRECT(), getAngle());
		moveCollidingObject(&getOwner(), -vec.x, -vec.y);
	}

	void CollisionComponentRectangleRotated::resolveCollisionBy(const CollisionComponentRectangleRotated * other)
	{
		//TODO
	}

	void CollisionComponentRectangleRotated::rotate(float dAngleRad)
	{
		_angleRad += dAngleRad;
	}

	void CollisionComponentRectangleRotated::setAngle(float angleRad)
	{
		_angleRad = angleRad;
	}

	void CollisionComponentRectangleRotated::setRECT(const RECT & rect)
	{
		_rect = rect;
	}

	RECT CollisionComponentRectangleRotated::getUnrotatedRECT() const {
		RECT rect = _rect;
		POINTFLOAT pos = _owner.getPosition();
		rect.left = _rect.left + pos.x;
		rect.right = _rect.right + pos.x;
		rect.top = _rect.top + pos.y;
		rect.bottom = _rect.bottom+ pos.y;
		return rect;
	}
}