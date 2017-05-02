#pragma once
#include "PlayerState.h"
class Player;
class PlayerStateCrawling :public PlayerState
{
public:
	PlayerStateCrawling();
	virtual ~PlayerStateCrawling();
	void enter(Player& player);
	void finish(Player& player);
	PlayerState* update(Player& player);
};

