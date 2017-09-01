#pragma once
#include "PlayerStateIface.h"
#include "SpritesAnimation.h"
#include "AnimationLRPair.h"
namespace SGA {
	class PlayerStateWalking :
		public PlayerStateIface
	{
		enum SubStates {
			IDLE,
			LIFTING_HEAD,
			FIRING,
			GRENADE,
			KNIFE,
			KNEEING_DOWN
		};
	public:
		PlayerStateWalking(Player & player);
		virtual ~PlayerStateWalking();
		void update();
		void render();
		void enterState(PlayerStateIface* prev);
		void exitState();
	private:
		void updateState();
		void moveUpdate();
		void processKeyInput();
		void initAnimation();
		void fire();
	private:
		int _knifeIdx;
		SubStates _subState;
		SpritesAnimation* _animation;

		AnimationLRPair _animLowerWalk;
		AnimationLRPair _animUpperWalk;
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		AnimationLRPair _animUpperFire;
		AnimationLRPair _animUpperWatchUpFire;
		AnimationLRPair _animUpperGrenade;
		AnimationLRPair _animUpperKnife[2];

		AnimationLRPair _animKneeWalk;
		AnimationLRPair _animKneeIdle;
		AnimationLRPair _animAllKneeTurn;
		AnimationLRPair _animToKnee;
		AnimationLRPair _animFromKnee;
		AnimationLRPair _animKneeIdleAfterGrenade;
		AnimationLRPair _animKneeFire;
		AnimationLRPair _animKneeGrenade;
		AnimationLRPair _animKneeKnife[2];

		AnimationLRPair _animUpperReload;
	};
}