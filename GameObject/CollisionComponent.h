#pragma once
#include <unordered_set>
#include <algorithm>
#include <Windows.h>
namespace SGA {

	enum CollisionLayers {
		COLLISION_LAYER1 = 0,
		COLLISION_LAYER2,
		COLLISION_LAYER3,
		COLLISION_LAYER4,
		COLLISION_LAYER5,
		COLLISION_LAYER6,
		COLLISION_LAYER7,
		COLLISION_LAYER8,

		NUM_COLLISION_LAYER
	};
	class GameObject;
	class CollisionComponentCircle;
	class CollisionComponentRectangle;
	class CollisionComponentRectangleRotated;
	class CollisionComponent {
	public:
		CollisionComponent(GameObject& owner, bool isTrigger, CollisionLayers collisionLayer);

		virtual ~CollisionComponent() {}

		//other와 충돌한다면 true를 반환한다.
		virtual bool isCollideWith(const CollisionComponent* other) const = 0;
		//더블 디스패치를 위한 오버로딩 메서드
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentRectangleRotated* other) const = 0;

		//other의 위치를 수정하여 충돌을 해제시킨다.
		virtual void resolveCollisionWith(CollisionComponent* other) const = 0;
		//더블 디스패치를 위한 오버로딩 메서드
		virtual void resolveCollisionBy(const CollisionComponentRectangle* other) = 0;
		virtual void resolveCollisionBy(const CollisionComponentCircle* other) = 0;
		virtual void resolveCollisionBy(const CollisionComponentRectangleRotated* other) = 0;

		//Owner의 위치에 대한 충돌 컴포넌트의 상대 위치를 설정한다.
		//충돌 검출 시에 onwer의 현재 위치를 오프셋시켜 충돌 컴포넌트의 위치를 결정한다.
		void setOffset(float offsetX, float offsetY);

		//other와 충돌 중에 호출해야 한다.
		void handleCollision(CollisionComponent* other);

		//other와 충돌이 일어나고 있지 않을 때 호출해야 한다.
		void handleNoneCollision(CollisionComponent* other);

		//other의 충돌 레이어 마스크를 비교하여 충돌 체크 수행 여부를 반환한다.
		bool isCollidableWith(const CollisionComponent* other) {
			//return _collisionMask & other->_collisionMask;
			return _layerInteraction[_collisionLayer][other->_collisionLayer];
		}

		//충돌 레이어를 설정한다.
		void setCollisionLayer (CollisionLayers layer) {
			_collisionLayer = layer;
		}

		//현재 충돌 레이어를 반환한다.
		CollisionLayers getCollisionLayer() const {
			return _collisionLayer;
		}

		//충돌 컴포넌트를 소유하고 있는 GameObject의 참조를 반환한다.
		GameObject& getOwner() { 
			return _owner; 
		}

		//trigger여부를 반환한다.
		bool isTrigger() const { 
			return _isTrigger;
		}
		
		static void enableCollisionBetweenLayers(CollisionLayers layer1, CollisionLayers layer2);
		static void disableCollisionBetweenLayers(CollisionLayers layer1, CollisionLayers layer2);
		static void enableCollisionsBetweenAllLayers();
		static void disableCollisionsBetweenAllLayers();
	protected:
		void moveCollidingObject(GameObject* object, float dx, float dy);
	protected:
		//Owner의 위치에 대한 충돌 컴포넌트의 상대 위치
		//기본값을 (0,0)이다.
		POINTFLOAT _offset;
		std::unordered_set<CollisionComponent*> _collisionMemory;
		//기본값 : COLLISION_LAYER1
		CollisionLayers _collisionLayer;
		GameObject& _owner;
		bool _isTrigger;
	private:
		static bool _layerInteraction[NUM_COLLISION_LAYER][NUM_COLLISION_LAYER];
	};
}