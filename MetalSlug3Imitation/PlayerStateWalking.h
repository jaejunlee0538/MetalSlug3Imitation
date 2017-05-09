#pragma once
#include "PlayerStateIface.h"
#include <SpritesAnimation.h>
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
			KNIFE
		};
	public:
		PlayerStateWalking(Player & player);
		virtual ~PlayerStateWalking();
		void update();
		void render();
		void enterState(PlayerStateIface* prev);
		void exitState();
	private:
		void initAnimation();
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

		AnimationLRPair _animUpperReload;
	};
}