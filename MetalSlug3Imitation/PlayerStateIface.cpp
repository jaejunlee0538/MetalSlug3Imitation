#include "PlayerStateIface.h"
#include "Player.h"
#include "PlayerStateCrawling.h"
#include "PlayerStateJumping.h"
#include "PlayerStateJumpingForward.h"
#include "PlayerStateKneeing.h"
#include "PlayerStateStanding.h"
#include "PlayerStateWalking.h"

namespace SGA {
	PlayerStateIface::PlayerStateMap PlayerStateIface::createPlayerStateMap(Player & player)
	{
		PlayerStateMap stateMap;
		stateMap[PlayerStates::STANDING] = new PlayerStateStanding(player);
		//stateMap[PlayerStates::WALKING] = new PlayerStateWalking(player);
		//stateMap[PlayerStates::CRAWLING] = new PlayerStateCrawling(player);
		//stateMap[PlayerStates::JUMPING] = new PlayerStateJumping(player);
		//stateMap[PlayerStates::JUMPING_FORWARD] = new PlayerStateJumpingForward(player);
		//stateMap[PlayerStates::KNEEING] = new PlayerStateKneeing(player);

		return stateMap;
	}
}