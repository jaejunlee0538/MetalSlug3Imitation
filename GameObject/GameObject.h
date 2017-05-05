#pragma once
#include <Windows.h>
#include <string>
#include "CollisionComponent.h"
#include <list>
namespace SGA {

	class GameObject
	{
	public:
		GameObject()
		{
			setPosition(0, 0);
			setInactive();
		}

		virtual ~GameObject()
		{

		}

		virtual std::string getTag() const = 0;
		//////////////////////////////////////////////////////////////
		void addChild(GameObject* child) {
			_childs.push_back(child);
			child->_parent = this;
		}
		
		inline std::list<GameObject*>::iterator beginChilds() {
			return _childs.begin();
		}

		inline std::list<GameObject*>::iterator endChilds() {
			return _childs.end();
		}
		//////////////////////////////////////////////////////////////
		virtual void update() = 0;
		//////////////////////////////////////////////////////////////
		virtual bool isRenderable() const = 0;
		virtual void render() {}
		///////////////////충돌 관련////////////////////////////////////
		bool isCollidable() const {
			return _collisionComponent != NULL;
		}
		CollisionComponent* setCollisionComponent(CollisionComponent* collisionComponent) {
			CollisionComponent* old = _collisionComponent;
			_collisionComponent = collisionComponent;
			return old;
		}
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
		inline void setPosition(float x, float y) {
			_position.x = x;
			_position.y = y;
		}

		inline POINTFLOAT getPosition() const {
			POINTFLOAT pos= _position;
			if (_parent) {
				POINTFLOAT parentPos = _parent->getPosition();
				pos.x += parentPos.x;
				pos.y += parentPos.y;
			}
			return pos;
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
	private:
		bool _isActive;
		POINTFLOAT _position;
		CollisionComponent * _collisionComponent = NULL;
		GameObject* _parent = NULL;
		std::list<GameObject*> _childs;
	};
}