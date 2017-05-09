#include "PlayerStateJumping.h"
#include <KeyManager.h>
#include "Player.h"
namespace SGA {
	PlayerStateJumping::PlayerStateJumping(Player & player) :PlayerStateIface(player) {
		initAnimation();
	}

	PlayerStateJumping::~PlayerStateJumping()
	{
	}

	void PlayerStateJumping::update()
	{
		//if (_player.isGrounded()) {
		//	_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
		//	return;
		//}
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
					if (isLookingDown()) {
						setUpperAnimation(_animUpperJumpWatchDownFire.get(_player.isLookingLeft()));
					}
					else if (_player.isLookingUp()) {
						setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
					}
					else {
						setUpperAnimation(_animUpperFire.get(_player.isLookingLeft()));
					}
					
					_subState = FIRING;
				}
			}

		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			setUpperAnimation(_animUpperJumpGrenade.get(_player.isLookingLeft()));
			_subState = GRENADE;
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			//TODO : 왼쪽으로 이동
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			//TODO : 오른쪽으로 이동
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			if (_player.isLookingUp() == false && isLookingDown() == false) {
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				_player.setLookingUp(true);
				_subState = LIFTING_HEAD;
			}
		}
		else {
			if (_player.isLookingUp()&& isLookingDown() == false) {
				setUpperAnimation(_animUpperFromWatchUp.get(_player.isLookingLeft()));
				_player.setLookingUp(false);
				_subState = LIFTING_HEAD;
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			//아래 쳐다보기
			if (isLookingDown() == false && _player.isLookingUp() == false) {
				setLookingDown(true);
				setUpperAnimation(_animUpperToJumpWatchDown.get(_player.isLookingLeft()));
				_subState = LOWERING_HEAD;
			}
		}
		else {
			if (isLookingDown() && _player.isLookingUp() == false) {
				setLookingDown(false);
				setUpperAnimation(_animUpperFromJumpWatchDown.get(_player.isLookingLeft()));
				_subState = LOWERING_HEAD;
			}
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
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case LOWERING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (isLookingDown()) {
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}

				_subState = IDLE;
			}
		}
		break;
		case FIRING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (isLookingDown()) {
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				else if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case GRENADE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (isLookingDown()) {
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				else if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case KNIFE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				_subState = IDLE;
			}
		}
		break;
		}
	}

	void PlayerStateJumping::enterState(PlayerStateIface * prev)
	{
		_subState = IDLE;
		_knifeIdx = 0;
		setLookingDown(false);
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
			setLookingDown(true);
		}
		else if (_player.isLookingUp()) {
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
		}
		else {
			setUpperAnimation(_animUpperJump.get(_player.isLookingLeft()));
		}
		setLowerAnimation(_animLowerJump.get(_player.isLookingLeft()));
	}

	void PlayerStateJumping::exitState()
	{

	}

	void PlayerStateJumping::initAnimation()
	{
		_knifeIdx = 0;
		_animLowerJump.init("Tarma_Normal_Pistol_Lower_Jump");
		_animUpperJump.init("Tarma_Normal_Pistol_Upper_Jump");
		_animUpperStandIdle.init("Tarma_Normal_Pistol_Upper_StandIdle");
		_animUpperWatchUpIdle.init("Tarma_Normal_Pistol_Upper_WatchUpIdle");
		_animUpperToWatchUp.init("Tarma_Normal_Pistol_Upper_ToWatchUp");
		_animUpperFromWatchUp.init("Tarma_Normal_Pistol_Upper_FromWatchUp");
		_animUpperFire.init("Tarma_Normal_Pistol_Upper_StandFire");
		_animUpperWatchUpFire.init("Tarma_Normal_Pistol_Upper_WatchUpFire");
		_animUpperJumpWatchDown.init("Tarma_Normal_Pistol_Upper_JumpWatchDown");
		_animUpperToJumpWatchDown.init("Tarma_Normal_Pistol_Upper_JumpWatchDown");
		_animUpperFromJumpWatchDown.init("Tarma_Normal_Pistol_Upper_JumpWatchDown");

		_animUpperJumpWatchDownFire.init("Tarma_Normal_Pistol_Upper_JumpWatchDownFire");
		_animUpperJumpGrenade.init("Tarma_Normal_Pistol_Upper_JumpGrenade");
		_animUpperKnife[0].init("Tarma_Normal_Pistol_Upper_StandKnifeA");
		_animUpperKnife[1].init("Tarma_Normal_Pistol_Upper_StandKnifeB");
	}
}