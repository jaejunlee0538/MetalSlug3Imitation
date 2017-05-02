#pragma once
#include "PlayerState.h"

class Player;
class PlayerStateKneeing :public PlayerState
{
public:
	PlayerStateKneeing();
	virtual ~PlayerStateKneeing();
	void enter(Player& player);
	void finish(Player& player);
	PlayerState* update(Player& player);

};

