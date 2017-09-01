#pragma once
#include "Enemy.h"
#include "SpritesAnimation.h"
#include "AnimationLRPair.h"
namespace SGA {
	class ChoumenConga :
		public Enemy
	{
		enum struct AnimID {
			IDLE=0,
			FUNMOTION_EATING,
			JUMP,
			TURN,
			WALK,
			FIRE_BUBBLE,
			CLOSE_ATTACK,
			DIE_NORMAL,
			DIE_BURST
		};
	public:
		ChoumenConga(std::string tag);
		virtual ~ChoumenConga();

	private:
		void initAnimation();
	private:
		AnimationLRPair* _currentAnim;

		AnimationLRPair _animIdle;
		AnimationLRPair _animEating;
		AnimationLRPair _animJump;
		AnimationLRPair _animTurn;
		AnimationLRPair _animWalk;
		AnimationLRPair _animFireBubble;
		AnimationLRPair _animClawAttack;
		AnimationLRPair _animDieNormal;
		AnimationLRPair _animDieBurst;
	};
}