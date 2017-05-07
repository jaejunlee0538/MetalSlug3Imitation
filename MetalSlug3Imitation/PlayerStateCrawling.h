#pragma once
#include "PlayerStateIface.h"
namespace SGA {
	class PlayerStateCrawling :
		public PlayerStateIface
	{
	public:
		PlayerStateCrawling(Player & player);
		virtual ~PlayerStateCrawling();
	};

}