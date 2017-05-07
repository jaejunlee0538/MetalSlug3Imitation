#pragma once
#include "Enemy.h"
#include <SpritesAnimation.h>
namespace SGA {
	class ChoumenConga :
		public Enemy
	{
		enum struct AnimID {
			IDLE=0,
			FUNMOTION,
			JUMP,
			TURN,
			WALK,
			FIRE_BUBBLE,
			CLOSE_ATTACK,
			DIE_NORMAL,
			DIE_BURST
		};
	public:
		ChoumenConga(std::string tag, int hp, int width, int height, int alterRangeRadius);
		virtual ~ChoumenConga();

	private:
		SpritesAnimation* _animIdle[2];
	};
}