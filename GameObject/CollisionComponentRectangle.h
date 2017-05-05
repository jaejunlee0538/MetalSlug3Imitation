#pragma once
#include "CollisionComponent.h"
#include "CollisionCheckFunc.h"
namespace SGA {
	class CollisionComponentCircle;
	class CollisionComponentRectangle : public CollisionComponent {
	public:
		CollisionComponentRectangle(GameObject& owner, RECT rect, bool isTrigger, uint8_t collisionMask);

		virtual bool isCollideWith(const CollisionComponent* other) const;
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other)const;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other)const;

		RECT getCollisionRECT() const;

		void setRECT(const RECT& rect) {
			_rect = rect;
		}
	private:
		RECT _rect;
	};
}