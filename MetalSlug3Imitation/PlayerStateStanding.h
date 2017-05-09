#pragma once
#include "PlayerStateIface.h"
#include "WorldClock.h"
#include "AnimationLRPair.h"
namespace SGA {
	class PlayerStateStanding :
		public PlayerStateIface
	{
	public:
		enum SubStates {
			IDLE,
			TURNING,
			LIFTING_HEAD,
			FIRING,
			GRENADE,
			KNIFE,
			FUNMOTION
		};
		PlayerStateStanding(Player & player);
		virtual ~PlayerStateStanding();

		void update();
		void enterState(PlayerStateIface * prev);
		void exitState();
	private:
		void initAnimation();
		void stateUpdate();
	private:
		SubStates _subState;
		SpritesAnimation * _currentUpperAnimation;
		SpritesAnimation * _currentLowerAnimation;

		int _knifeIdx;

		bool _isNextAll;
		SpritesAnimation * _nextAnimationAll;
		SpritesAnimation * _nextAnimationUpper;
		SpritesAnimation * _nextAnimationLower;

		//가만히 서있을 때
		AnimationLRPair _animUpperStandIdle;
		AnimationLRPair _animLowerStandIdle;
		AnimationLRPair _animUpperStandFire;
		AnimationLRPair _animAllStandKnifing[2];
		AnimationLRPair _animUpperStandGrenade;
		/////////////////////////////////////////
		//위 쳐다보고 있을 때
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperWatchUpFire;
		/////////////////////////////////////////
		AnimationLRPair _animAllTurn;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		/////////////////////////////////////////
		//기타 애니메이션
		AnimationLRPair _animAllBrake;
		AnimationLRPair _animUpperFunMotion[2];
		AnimationLRPair _animReload;

		TimeoutChecker _funMotionTimeout;
	};
}