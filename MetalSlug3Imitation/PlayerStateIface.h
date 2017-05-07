#pragma once
#include <map>
#include <assert.h>
#include <SpritesAnimation.h>
namespace SGA {
	enum struct PlayerStates {
		STANDING,
		WALKING,
		CRAWLING,
		JUMPING,
		JUMPING_FORWARD,
		KNEEING
	};
	class Player;
	class PlayerStateIface
	{
	public:
		typedef std::map<PlayerStates, PlayerStateIface*> PlayerStateMap;
		PlayerStateIface(Player& player)
		:_player(player){
		}

		virtual ~PlayerStateIface() {
		}

		virtual void update() = 0;
		virtual void render() = 0;
		virtual void enterState() = 0;
		virtual void exitState() = 0;

		static PlayerStateMap createPlayerStateMap(Player& player);
	protected:
		Player& _player;
	};
}