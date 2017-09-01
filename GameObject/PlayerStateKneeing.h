#pragma once
#include "PlayerStateIface.h"
namespace SGA {
	class PlayerStateKneeing : public PlayerStateIface
	{
	public:
		PlayerStateKneeing(Player & player);
		~PlayerStateKneeing();
	};

}