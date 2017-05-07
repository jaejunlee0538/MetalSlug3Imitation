#pragma once
#include "PlayerStateIface.h"
#include <SpritesAnimation.h>
namespace SGA {
	class PlayerStateWalking :
		public PlayerStateIface
	{
	public:
		PlayerStateWalking(Player & player);
		virtual ~PlayerStateWalking();
		void update();
		void render();
		void enterState();
		void exitState();
	private:
		SpritesAnimation* _animation;
	};
}