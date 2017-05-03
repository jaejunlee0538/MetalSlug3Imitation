#pragma once
#include "PlayerState.h"
namespace SGA {
	class Player;
	class PlayerStateJumpingForward :public PlayerState
	{
	public:
		PlayerStateJumpingForward();
		virtual ~PlayerStateJumpingForward();
		void enter(Player& player);
		void finish(Player& player);
		PlayerState* update(Player& player);

	};

}