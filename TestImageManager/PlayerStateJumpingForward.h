#pragma once
#include "PlayerState.h"

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

