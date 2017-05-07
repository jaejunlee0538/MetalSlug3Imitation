#pragma once
#include <Windows.h>
#include <string>
#include "CollisionComponent.h"
#include <list>
namespace SGA {

	class GameObject
	{
	public:
		GameObject();

		virtual ~GameObject();

		virtual std::string getTag() const = 0;
		virtual GameObject* clone() { return NULL; }
		//////////////////////////////////////////////////////////////
		GameObject* getParent();
		void addChild(GameObject* child);
		
		inline std::list<GameObject*>::iterator beginChilds() {
			return _childs.begin();
		}

		inline std::list<GameObject*>::iterator endChilds() {
			return _childs.end();
		}
		//////////////////////////////////////////////////////////////
		virtual void update() {}
		//////////////////////////////////////////////////////////////
		virtual bool isRenderable() const = 0;
		virtual void render() {}
		///////////////////�浹 ����////////////////////////////////////
		virtual bool isCollidable() const {
			return _collisionComponent != NULL;
		}

		CollisionComponent* setCollisionComponent(CollisionComponent* collisionComponent);
		CollisionComponent* getCollisionComponent() { 
			return _collisionComponent; 
		}
		virtual void onCollidingEnter(GameObject& other) {}
		virtual void onColliding(GameObject& other) {}
		virtual void onCollidingExit(GameObject& other) {}
		virtual void onTrigerringEnter(GameObject& other){}
		virtual void onTrigerring(GameObject& other) {}
		virtual void onTrigerringExit(GameObject& other) {}
		///////////////////////////////////////////////////////////////////
		virtual void movePosition(float dx, float dy);
		virtual void setPosition(float x, float y);
		POINTFLOAT getPosition() const;
		POINTFLOAT getDeltaPosition() const;

		void enableGravity() {
			_useGravity = true;
		}

		void disableGravity() {
			_useGravity = false;
		}

		bool isGravityEnabled() const {
			return _useGravity;
		}

		void enableKinematic() {
			_isKinematic = true;
		}

		void disableKinamatic() {
			_isKinematic = false;
		}

		bool isKinematic() const {
			return _isKinematic;
		}

		void setActive() {
			_isActive = true;
		}
		void setInactive() {
			_isActive = false;
		}
		bool isActive() const {
			return _isActive;
		}
		
		//////////
		//�ڽŰ� �ڽ� ������Ʈ���� ��� �浹 ������Ʈ�� ���� beginCollisionCheck�� ȣ���Ѵ�.
		void beginCollisionCheck();
		//�ڽŰ� �ڽ� ������Ʈ���� ��� �浹 ������Ʈ�� ���� endCollisionCheck�� ȣ���Ѵ�.
		void endCollisionCheck();
		//this�� this�� ��� �ڽİ� other�� other�� ��� �ڽ� ������ �浹üũ�� �����Ѵ�.
		void checkCollisionWith(GameObject* other);
	private:
		void __resolveCollision(GameObject* other);
		void __collisionCheckInternal(GameObject* other, bool ccc);
	private:
		bool _isActive;//�⺻�� : true
		bool _useGravity;//�⺻�� : true
		bool _isKinematic;//�⺻�� : false
		POINTFLOAT _position;
		POINTFLOAT _deltaPos;
		CollisionComponent * _collisionComponent = NULL;
		GameObject* _parent = NULL;
		std::list<GameObject*> _childs;
	};
}