#pragma once
#include "PlayerStateIface.h"
namespace SGA {
	class PlayerStateJumping :
		public PlayerStateIface
	{
	public:
		PlayerStateJumping(Player & player);
		~PlayerStateJumping();
	};

}