#pragma once
#include <Windows.h>
#include "LayerManager.h"
namespace SGA {
	enum GameObjectTypes {
		GAME_OBJECT_PLAYER,
		GAME_OBJECT_ENEMY,
		GAME_OBJECT_BULLET,
		GAME_OBJECT_FATAL_ZONE,
		GAME_OBJECT_TRIGGERING_BOX,
		GAME_OBJECT_DESTRUCTABLE_STRUCTURE
	};

	enum CollisionTypes {
		COLLISION_TYPE_RECT,
		COLLISION_TYPE_CIRCLE
	};

	class Bullet;
	class EnemyObject;
	class PlayerObject;
	class GameObject {
	public:
		GameObject(){
			_layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_GAME_OBJECT);
		}
		virtual ~GameObject(){}
	
		virtual void update(){}

		virtual void render(){}

		virtual const RECT& getCollisionRect() const = 0;
		virtual const CollisionTypes getCollisionType() const = 0;
		virtual void onCollision(GameObject* other) {}

		virtual void killedBy(Bullet* bullet) {}
		virtual void killedBy(EnemyObject* bullet) {}
		virtual void killedBy(PlayerObject * bullet) {}

		virtual GameObjectTypes getTypeID() const = 0;

		virtual bool isDestructable() const = 0;
		virtual bool isDestroied() const = 0;

		virtual void movePosition(float dx, float dy) {
			_position.x += dx;
			_position.y += dy;
		}

		virtual void setPosition(float x, float y) {
			_position.x = x;
			_position.y = y;
		}

		virtual const POINTFLOAT& getPosition() const {
			return _position;
		}

		virtual void setLookingLeft(bool lookLeft) {
			_lookingLeft = lookLeft;
		}

		virtual bool isLookingLeft() const {
			return _lookingLeft;
		}

		int getHP() const {
			return _hp;
		}

		void setHP(int hp) {
			if (hp < 0) {
				hp = 0;
			}
			_hp = hp;
		}
	protected:
		Layer* _layer;
	private:
		int _hp;
		POINTFLOAT _position;
		bool _lookingLeft;
	};
}