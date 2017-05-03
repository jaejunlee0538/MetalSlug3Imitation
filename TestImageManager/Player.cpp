#include "Player.h"
#include "SpritesAnimation.h"
#include "Stdafx.h"
#include "PlayerStateStanding.h"
namespace SGA {
	Player::Player()
	{
		_state = new PlayerStateStanding();
		_state->enter(*this);
	}


	Player::~Player()
	{
	}

	void Player::update()
	{
		PlayerState* newState = _state->update(*this);
		if (newState != NULL) {
			_state->finish(*this);
			delete _state;
			_state = newState;
			_state->enter(*this);
		}

		for (auto it = _animations.begin(); it != _animations.end(); ++it) {
			(*it)->update();
		}

	}

	void Player::render(HDC hdc)
	{
		for (auto it = _animations.begin(); it != _animations.end(); ++it) {
			(*it)->render(hdc, _x, _y);
		}
	}
}