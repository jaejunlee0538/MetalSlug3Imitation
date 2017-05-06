#pragma once
#include "CollisionComponent.h"
namespace SGA {
	class CollisionComponentRectangleRotated : public CollisionComponent
	{
	public:
		CollisionComponentRectangleRotated(GameObject& owner, RECT rect, float angleRad, bool isTrigger, CollisionLayers collisionLayer);
		virtual ~CollisionComponentRectangleRotated();

		virtual bool isCollideWith(const CollisionComponent* other) const;
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other)const;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other)const;
		virtual bool implCollisionCheck(const CollisionComponentRectangleRotated* other) const;

		virtual void resolveCollisionWith(CollisionComponent* other) const;
		virtual void resolveCollisionBy(const CollisionComponentRectangle* other);
		virtual void resolveCollisionBy(const CollisionComponentCircle* other);
		virtual void resolveCollisionBy(const CollisionComponentRectangleRotated* other);

		void rotate(float dAngleRad);
		void setAngle(float angleRad);
		void setRECT(const RECT& rect);
		float getAngle() const {
			return _angleRad;
		}

		RECT getUnrotatedRECT() const;
	private:
		RECT _rect;
		float _angleRad;
	};

}