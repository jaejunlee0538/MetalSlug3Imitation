#pragma once
#include "PlayerState.h"
namespace SGA {
	class Player;
	class PlayerStateJumping :public PlayerState
	{
	public:
		PlayerStateJumping();
		virtual ~PlayerStateJumping();
		void enter(Player& player);
		void finish(Player& player);
		PlayerState* update(Player& player);
	private:
		float _speed;
		float _gravity;
	};

}