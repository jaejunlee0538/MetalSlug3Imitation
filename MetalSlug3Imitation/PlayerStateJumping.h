#pragma once
#include "PlayerStateIface.h"
#include <SpritesAnimation.h>
#include "AnimationLRPair.h"
namespace SGA {
	class PlayerStateJumping :
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
		PlayerStateJumping(Player & player);
		~PlayerStateJumping();
		void update();
		void enterState(PlayerStateIface * prev);
		void exitState();
		inline void setLookingDown(bool lookDown) {
			_lookingDown = lookDown;
		}
		inline bool isLookingDown() const {
			return _lookingDown;
		}
	private:
		void initAnimation();
	private:
		bool _lookingDown;
		SubStates _subState;
		int _knifeIdx;
		AnimationLRPair _animLowerJump;
		AnimationLRPair _animUpperJump;
		AnimationLRPair _animUpperStandIdle;
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		AnimationLRPair _animUpperFire;
		AnimationLRPair _animUpperWatchUpFire;
		AnimationLRPair _animUpperJumpWatchDown;
		AnimationLRPair _animUpperToJumpWatchDown;//임시
		AnimationLRPair _animUpperFromJumpWatchDown;//임시

		AnimationLRPair _animUpperJumpWatchDownFire;
		AnimationLRPair _animUpperJumpGrenade;
		AnimationLRPair _animUpperKnife[2];
	};
}