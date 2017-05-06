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

		//other�� �浹�Ѵٸ� true�� ��ȯ�Ѵ�.
		virtual bool isCollideWith(const CollisionComponent* other) const = 0;
		//���� ����ġ�� ���� �����ε� �޼���
		virtual bool implCollisionCheck(const CollisionComponentRectangle* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentCircle* other) const = 0;
		virtual bool implCollisionCheck(const CollisionComponentRectangleRotated* other) const = 0;

		//other�� ��ġ�� �����Ͽ� �浹�� ������Ų��.
		virtual void resolveCollisionWith(CollisionComponent* other) const = 0;
		//���� ����ġ�� ���� �����ε� �޼���
		virtual void resolveCollisionBy(const CollisionComponentRectangle* other) = 0;
		virtual void resolveCollisionBy(const CollisionComponentCircle* other) = 0;
		virtual void resolveCollisionBy(const CollisionComponentRectangleRotated* other) = 0;

		//Owner�� ��ġ�� ���� �浹 ������Ʈ�� ��� ��ġ�� �����Ѵ�.
		//�浹 ���� �ÿ� onwer�� ���� ��ġ�� �����½��� �浹 ������Ʈ�� ��ġ�� �����Ѵ�.
		void setOffset(float offsetX, float offsetY);

		//other�� �浹 �߿� ȣ���ؾ� �Ѵ�.
		void handleCollision(CollisionComponent* other);

		//other�� �浹�� �Ͼ�� ���� ���� �� ȣ���ؾ� �Ѵ�.
		void handleNoneCollision(CollisionComponent* other);

		//other�� �浹 ���̾� ����ũ�� ���Ͽ� �浹 üũ ���� ���θ� ��ȯ�Ѵ�.
		bool isCollidableWith(const CollisionComponent* other) {
			//return _collisionMask & other->_collisionMask;
			return _layerInteraction[_collisionLayer][other->_collisionLayer];
		}

		//�浹 ���̾ �����Ѵ�.
		void setCollisionLayer (CollisionLayers layer) {
			_collisionLayer = layer;
		}

		//���� �浹 ���̾ ��ȯ�Ѵ�.
		CollisionLayers getCollisionLayer() const {
			return _collisionLayer;
		}

		//�浹 ������Ʈ�� �����ϰ� �ִ� GameObject�� ������ ��ȯ�Ѵ�.
		GameObject& getOwner() { 
			return _owner; 
		}

		//trigger���θ� ��ȯ�Ѵ�.
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
		//Owner�� ��ġ�� ���� �浹 ������Ʈ�� ��� ��ġ
		//�⺻���� (0,0)�̴�.
		POINTFLOAT _offset;
		std::unordered_set<CollisionComponent*> _collisionMemory;
		//�⺻�� : COLLISION_LAYER1
		CollisionLayers _collisionLayer;
		GameObject& _owner;
		bool _isTrigger;
	private:
		static bool _layerInteraction[NUM_COLLISION_LAYER][NUM_COLLISION_LAYER];
	};
}