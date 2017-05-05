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

		//Owner�� ��ġ�� ���� �浹 ������Ʈ�� ��� ��ġ�� �����Ѵ�.
		//�浹 ���� �ÿ� onwer�� ���� ��ġ�� �����½��� �浹 ������Ʈ�� ��ġ�� �����Ѵ�.
		void setOffset(float offsetX, float offsetY);

		//other�� �浹 �߿� ȣ���ؾ� �Ѵ�.
		void handleCollision(CollisionComponent* other);

		//other�� �浹�� �Ͼ�� ���� ���� �� ȣ���ؾ� �Ѵ�.
		void handleNoneCollision(CollisionComponent* other);

		//other�� �浹 ���̾� ����ũ�� ���Ͽ� �浹 üũ ���� ���θ� ��ȯ�Ѵ�.
		bool isCollidableWith(const CollisionComponent* other) {
			return _collisionMask & other->_collisionMask;
		}

		//�浹 ���̾� ����ũ�� �����Ѵ�.
		void setCollisionLayer (uint8_t mask) {
			_collisionMask = mask;
		}

		//layer ���̾� ����ũ�� Ȱ��ȭ�Ѵ�.
		void enableCollisionLayer(CollisionLayers layer) {
			_collisionMask |= COLLISION_LAYER1;
		}

		//layer ���̾� �������� ��Ȱ��ȭ �Ѵ�.
		void disableCollisionLayer(CollisionLayers layer) {
			_collisionMask &= ~COLLISION_LAYER1;
		}

		//�浹 ������Ʈ�� �����ϰ� �ִ� GameObject�� ������ ��ȯ�Ѵ�.
		GameObject& getOwner() { 
			return _owner; 
		}

		//trigger���θ� ��ȯ�Ѵ�.
		bool isTrigger() const { 
			return _isTrigger;
		}
	protected:
		//Owner�� ��ġ�� ���� �浹 ������Ʈ�� ��� ��ġ
		//�⺻���� (0,0)�̴�.
		POINTFLOAT _offset;
		std::unordered_set<CollisionComponent*> _collisionMemory;
		uint8_t _collisionMask;
		GameObject& _owner;
		bool _isTrigger;
	};
}