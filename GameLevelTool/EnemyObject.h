#pragma once
#include "GameObject.h"
namespace SGA {
	class EnemyObject :public GameObject
	{
	public:
		EnemyObject();
		virtual ~EnemyObject();
		virtual void update();
		virtual void render();
		virtual void onCollision(GameObject* other);
		virtual GameObjectTypes getTypeID() const {
			return GAME_OBJECT_ENEMY;
		}
	};
}