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
			FUNMOTION,
			KNEEING_DOWN
		};
		PlayerStateStanding(Player & player);
		virtual ~PlayerStateStanding();

		void update();
		void enterState(PlayerStateIface * prev);
		void exitState();
	private:
		void initAnimation();
		void stateUpdate();
		void processKeyInput();
		void fire();
	private:
		SubStates _subState;
		SpritesAnimation * _currentUpperAnimation;
		SpritesAnimation * _currentLowerAnimation;

		int _knifeIdx;

		bool _isNextAll;
		SpritesAnimation * _nextAnimationAll;
		SpritesAnimation * _nextAnimationUpper;
		SpritesAnimation * _nextAnimationLower;

		//������ ������ ��
		AnimationLRPair _animUpperStandIdle;
		AnimationLRPair _animLowerStandIdle;
		AnimationLRPair _animAllTurn;
		AnimationLRPair _animUpperStandFire;
		AnimationLRPair _animUpperStandKnifing[2];
		AnimationLRPair _animUpperStandGrenade;
		/////////////////////////////////////////
		//�� �Ĵٺ��� ���� ��
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperWatchUpFire;
		AnimationLRPair _animAllWatchUpTurn;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		/////////////////////////////////////////
		AnimationLRPair _animKneeIdle;
		AnimationLRPair _animAllKneeTurn;
		AnimationLRPair _animToKnee;
		AnimationLRPair _animFromKnee;
		AnimationLRPair _animKneeIdleAfterGrenade;
		AnimationLRPair _animKneeFire;
		AnimationLRPair _animKneeGrenade;
		AnimationLRPair _animKneeKnife[2];
		/////////////////////////////////////////
		//��Ÿ �ִϸ��̼�
		AnimationLRPair _animAllBrake;
		AnimationLRPair _animUpperFunMotion[2];
		AnimationLRPair _animReload;

		TimeoutChecker _funMotionTimeout;
	};
}