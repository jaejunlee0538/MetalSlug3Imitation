#pragma once
#include "PlayerStateIface.h"
namespace SGA {
	class PlayerStateCrawling :
		public PlayerStateIface
	{
		enum SubStates {
			IDLE,
			FIRING,
			GRENADE,
			KNIFE
		};
	public:
		PlayerStateCrawling(Player & player);
		virtual ~PlayerStateCrawling();
	};

}