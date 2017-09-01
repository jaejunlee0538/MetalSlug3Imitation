#pragma once
#include "PlayerStateIface.h"
#include "AnimationLRPair.h"
namespace SGA {
	class PlayerStateJumpingForward :
		public PlayerStateIface
	{
		enum SubStates {
			IDLE,
			LIFTING_HEAD,
			FIRING,
			GRENADE,
			KNIFE,
			LOWERING_HEAD
		};
	public:
		PlayerStateJumpingForward(Player & player);
		virtual ~PlayerStateJumpingForward();

		void update();
		void enterState(PlayerStateIface * prev);
		void exitState();
	private:
		void initAnimation();
		void processKeyInput();
		void stateUpdate();
		void fire();
	private:
		SubStates _subState;
		int _knifeIdx;
		AnimationLRPair _animLowerWalkJump;
		AnimationLRPair _animUpperWalkJump;
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		AnimationLRPair _animUpperStandFire;
		AnimationLRPair _animUpperWatchUpFire;
		AnimationLRPair _animUpperJumpWatchDown;
		AnimationLRPair _animUpperToJumpWatchDown;//�ӽ�
		AnimationLRPair _animUpperFromJumpWatchDown;//�ӽ�
		AnimationLRPair _animUpperJumpWatchDownFire;

		AnimationLRPair _animUpperJumpGrenade;
		AnimationLRPair _animUpperKnife[2];
	};

}