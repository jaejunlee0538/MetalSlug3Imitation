#pragma once
#include "PlayerState.h"

class Player;
class PlayerStateWalking:public PlayerState
{
public:
	PlayerStateWalking(bool isLeft);
	virtual ~PlayerStateWalking();
	void enter(Player& player);
	void finish(Player& player);
	PlayerState* update(Player& player);

private:
	float _speedX;
	bool _isLeft;
};

