#pragma once
#include "PlayerStateIface.h"
namespace SGA {
	class PlayerStateJumpingForward :
		public PlayerStateIface
	{
	public:
		PlayerStateJumpingForward(Player & player);
		virtual ~PlayerStateJumpingForward();
	};

}