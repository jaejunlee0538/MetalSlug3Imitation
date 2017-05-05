#pragma once
#include "CollisionComponent.h"
#include "CollisionCheckFunc.h"
#include <assert.h>
namespace SGA {
	class CollisionComponentRectangle;
	class CollisionComponentCircle : public CollisionComponent {
	public:
		CollisionComponentCircle(GameObject & owner, RECT circle, bool isTrigger, uint8_t collisionMask);

		virtual bool isCollideWith(const CollisionComponent* other) const;
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other) const;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other) const;

		RECT getCollisionRECT() const;

		void setRECT(const RECT& rect) {
			_rect = rect;
		}
	private:
		RECT _rect;
	};
}