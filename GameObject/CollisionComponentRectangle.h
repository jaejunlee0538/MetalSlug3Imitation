#pragma once
#include "CollisionComponent.h"
#include "CollisionCheckFunc.h"
namespace SGA {
	class CollisionComponentCircle;
	class CollisionComponentRectangle : public CollisionComponent {
	public:
		CollisionComponentRectangle(GameObject& owner, RECT rect, bool isTrigger, CollisionLayers collisionLayer);

		virtual bool isCollideWith(const CollisionComponent* other) const;
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other)const;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other)const;

		virtual void resolveCollisionWith(CollisionComponent* other) const;
		virtual void resolveCollisionBy(const CollisionComponentRectangle* other);
		virtual void resolveCollisionBy(const CollisionComponentCircle* other);

		RECT getCollisionRECT() const;

		void setRECT(const RECT& rect) {
			_rect = rect;
		}
	private:
		RECT _rect;
	};
}