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
		///////////////////충돌 관련////////////////////////////////////
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
		//자신과 자식 오브젝트들의 모든 충돌 컴포넌트에 대해 beginCollisionCheck를 호출한다.
		void beginCollisionCheck();
		//자신과 자식 오브젝트들의 모든 충돌 컴포넌트에 대해 endCollisionCheck를 호출한다.
		void endCollisionCheck();
		//this와 this의 모든 자식과 other와 other의 모든 자식 사이의 충돌체크를 수행한다.
		void checkCollisionWith(GameObject* other);
	private:
		void __resolveCollision(GameObject* other);
		void __collisionCheckInternal(GameObject* other, bool ccc);
	private:
		bool _isActive;//기본값 : true
		bool _useGravity;//기본값 : true
		bool _isKinematic;//기본값 : false
		POINTFLOAT _position;
		POINTFLOAT _deltaPos;
		CollisionComponent * _collisionComponent = NULL;
		GameObject* _parent = NULL;
		std::list<GameObject*> _childs;
	};
}