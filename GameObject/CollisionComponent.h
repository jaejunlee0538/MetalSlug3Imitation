#pragma once
#include <unordered_set>
#include <algorithm>
#include <Windows.h>
namespace SGA {
	enum CollisionLayers {
		COLLISION_LAYER1=0x01,
		COLLISION_LAYER2,
		COLLISION_LAYER3,
		COLLISION_LAYER4,
		COLLISION_LAYER5,
		COLLISION_LAYER6,
		COLLISION_LAYER7,
		COLLISION_LAYER8
	};
	class GameObject;
	class CollisionComponentCircle;
	class CollisionComponentRectangle;
	class CollisionComponent {
	public:
		CollisionComponent(GameObject& owner, bool isTrigger, uint8_t collisionMask);

		virtual ~CollisionComponent() {}

		virtual bool isCollideWith(const CollisionComponent* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other) const = 0;

		//Owner의 위치에 대한 충돌 컴포넌트의 상대 위치를 설정한다.
		//충돌 검출 시에 onwer의 현재 위치를 오프셋시켜 충돌 컴포넌트의 위치를 결정한다.
		void setOffset(float offsetX, float offsetY);

		//other와 충돌 중에 호출해야 한다.
		void handleCollision(CollisionComponent* other);

		//other와 충돌이 일어나고 있지 않을 때 호출해야 한다.
		void handleNoneCollision(CollisionComponent* other);

		//other의 충돌 레이어 마스크를 비교하여 충돌 체크 수행 여부를 반환한다.
		bool isCollidableWith(const CollisionComponent* other) {
			return _collisionMask & other->_collisionMask;
		}

		//충돌 레이어 마스크를 설정한다.
		void setCollisionLayer (uint8_t mask) {
			_collisionMask = mask;
		}

		//layer 레이어 마스크를 활성화한다.
		void enableCollisionLayer(CollisionLayers layer) {
			_collisionMask |= COLLISION_LAYER1;
		}

		//layer 레이어 마으스를 비활성화 한다.
		void disableCollisionLayer(CollisionLayers layer) {
			_collisionMask &= ~COLLISION_LAYER1;
		}

		//충돌 컴포넌트를 소유하고 있는 GameObject의 참조를 반환한다.
		GameObject& getOwner() { 
			return _owner; 
		}

		//trigger여부를 반환한다.
		bool isTrigger() const { 
			return _isTrigger;
		}
	protected:
		//Owner의 위치에 대한 충돌 컴포넌트의 상대 위치
		//기본값을 (0,0)이다.
		POINTFLOAT _offset;
		std::unordered_set<CollisionComponent*> _collisionMemory;
		uint8_t _collisionMask;
		GameObject& _owner;
		bool _isTrigger;
	};
}