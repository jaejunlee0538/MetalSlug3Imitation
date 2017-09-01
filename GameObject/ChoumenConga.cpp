#include "ChoumenConga.h"
#include "AnimationManager.h"
namespace SGA {
	ChoumenConga::ChoumenConga(std::string tag)
		:Enemy(tag, 200, 50, 60, 100)
	{
	}

	ChoumenConga::~ChoumenConga()
	{
	}

	void ChoumenConga::initAnimation()
	{
	/*	AnimationLRPair _animIdle;
		AnimationLRPair _animEating;
		AnimationLRPair _animJump;
		AnimationLRPair _animTurn;
		AnimationLRPair _animWalk;
		AnimationLRPair _animFireBubble;
		AnimationLRPair _animClawAttack;
		AnimationLRPair _animDieNormal;
		AnimationLRPair _animDieBurst;*/
		_animIdle.init("ChowmeinConga_Idle_Left");
	}
}