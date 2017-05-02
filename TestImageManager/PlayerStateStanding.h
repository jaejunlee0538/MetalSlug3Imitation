#pragma once
#include "PlayerState.h"
#include "SpritesAnimation.h"
#include <vector>
class Player;
namespace SGA {
	class Sprite;
}
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

