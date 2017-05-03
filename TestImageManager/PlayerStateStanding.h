#pragma once
#include "PlayerState.h"
#include "SpritesAnimation.h"
#include <vector>
namespace SGA {
	class Player;
	class Sprite;
	class PlayerStateStanding :public PlayerState
	{
	public:
		PlayerStateStanding();
		virtual ~PlayerStateStanding();
		void enter(Player& player);
		void finish(Player& player);
		PlayerState* update(Player& player);

	private:
		bool _isLeft;

	};

}