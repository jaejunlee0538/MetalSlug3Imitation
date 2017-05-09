#include "PlayerStateWalking.h"
#include <AnimationManager.h>
#include "Player.h"
#include <KeyManager.h>
namespace SGA {
	 PlayerStateWalking::PlayerStateWalking(Player & player) :PlayerStateIface(player) {
		 _knifeIdx = 0;
		 initAnimation();
	}

	PlayerStateWalking::~PlayerStateWalking()
	{
	}

	void PlayerStateWalking::update()
	{
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SPACE)) {
			if (_player.isLookingUp()) {
				setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
			}
			else {
				if ((_player.isLookingLeft() && _player.isLeftKnifeTriggerOn())
					|| (_player.isLookingLeft() == false && _player.isRightKnifeTriggerOn())) {
					setUpperAnimation(_animUpperKnife[_knifeIdx].get(_player.isLookingLeft()));
					_subState = KNIFE;
					_knifeIdx++;
					if (_knifeIdx == 2) {
						_knifeIdx = 0;
					}
				}
				else {
					setUpperAnimation(_animUpperFire.get(_player.isLookingLeft()));
					_subState = FIRING;
				}
			}

		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			setUpperAnimation(_animUpperGrenade.get(_player.isLookingLeft()));
			_subState = GRENADE;
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SHIFT)) {
			//점프
		}

		if (_player.isLookingLeft()) {
			if (GET_KEY_MANAGER()->isStayKeyUp(VK_LEFT)) {
				_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
				return;
			}
		}
		else {
			if (GET_KEY_MANAGER()->isStayKeyUp(VK_RIGHT)) {
				_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
				return;
			}
		}
		
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			if (_player.isLookingUp() == false) {
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				_player.setLookingUp(true);
				_subState = LIFTING_HEAD;
			}
		}
		else {
			if (_player.isLookingUp()) {
				setUpperAnimation(_animUpperFromWatchUp.get(_player.isLookingLeft()));
				_player.setLookingUp(false);
				_subState = LIFTING_HEAD;
			}
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			//앉기 시작
		}

		switch (_subState) {
		case IDLE:
		{

		}
		break;
		case LIFTING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case FIRING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperFire.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case GRENADE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case KNIFE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				_subState = IDLE;
			}
		}
		break;
		}
	}

	void PlayerStateWalking::render()
	{
	}

	void PlayerStateWalking::enterState(PlayerStateIface* prev)
	{
		_subState = IDLE;
		if (_player.isLookingUp()) {
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerWalk.get(_player.isLookingLeft()));
		}
		else {
			setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerWalk.get(_player.isLookingLeft()));
		}
	}

	void PlayerStateWalking::exitState()
	{
	}
	void PlayerStateWalking::initAnimation()
	{
		/*AnimationLRPair _animLowerWalk;
		AnimationLRPair _animUpperWalk;
		AnimationLRPair _animUpperWatchUpIdle;
		AnimationLRPair _animUpperToWatchUp;
		AnimationLRPair _animUpperFromWatchUp;
		AnimationLRPair _animUpperFire;
		AnimationLRPair _animUpperWatchUpFire;
		AnimationLRPair _animUpperGrenade;
		AnimationLRPair _animUpperKnife[2];

		AnimationLRPair _animUpperReload;*/
		_animLowerWalk.init("Tarma_Normal_Pistol_Lower_Walk");
		_animUpperWalk.init("Tarma_Normal_Pistol_Upper_Walk");
		_animUpperWatchUpIdle.init("Tarma_Normal_Pistol_Upper_WatchUpIdle");
		_animUpperToWatchUp.init("Tarma_Normal_Pistol_Upper_ToWatchUp");
		_animUpperFromWatchUp.init("Tarma_Normal_Pistol_Upper_FromWatchUp");
		_animUpperFire.init("Tarma_Normal_Pistol_Upper_StandFire");
		_animUpperWatchUpFire.init("Tarma_Normal_Pistol_Upper_WatchUpFire");
		_animUpperGrenade.init("Tarma_Normal_Pistol_Upper_StandGrenade");
		_animUpperKnife[0].init("Tarma_Normal_Pistol_Upper_StandKnifeA");
		_animUpperKnife[1].init("Tarma_Normal_Pistol_Upper_StandKnifeB");

	}
}