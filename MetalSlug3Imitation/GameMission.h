#pragma once
#include "GameState.h"
#include <list>
#include <vector>
namespace SGA {
	class SpritesAnimation;
	class Sprite;
	class GameObject;
	class Player;
	class EnemyObject;
	class GameMission : public GameState
	{
	public:
		GameMission(){}
		virtual ~GameMission(){}
		virtual void init();
		virtual void update();
		virtual void render();
	private:
	};
}