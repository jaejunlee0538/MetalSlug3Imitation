#include "EnemyObject.h"


namespace SGA {
	EnemyObject::EnemyObject()
	{
	}


	EnemyObject::~EnemyObject()
	{
	}

	void EnemyObject::update()
	{
	}

	void EnemyObject::render()
	{
	}

	void EnemyObject::onCollision(GameObject * other) {
		switch (other->getTypeID()) {
		case GAME_OBJECT_PLAYER:
			break;
		case GAME_OBJECT_FATAL_ZONE:
			break;
		case GAME_OBJECT_PLAYER_BULLET:
			break;
		}
	}
}