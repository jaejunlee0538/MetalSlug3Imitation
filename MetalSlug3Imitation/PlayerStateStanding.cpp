#include "PlayerStateStanding.h"
#include <AnimationManager.h>
#include <KeyManager.h>
#include "Player.h"
#include <RandomFunction.h>
namespace SGA {
	PlayerStateStanding::PlayerStateStanding(Player & player)
		:PlayerStateIface(player), _funMotionTimeout(GET_GAME_WORLD_CLOCK(), 5000) {
		initAnimation();
		_knifeIdx = 0;
	}

	PlayerStateStanding::~PlayerStateStanding()
	{

	}

	void PlayerStateStanding::update()
	{
		//애니메이션이 다른 스테이트 객체로 전달될 수도 있기 대문에 update는 Player가 직접 호출하자.
		stateUpdate();
	}

	void PlayerStateStanding::enterState(PlayerStateIface * prev)
	{
		_subState = IDLE;
		if (_player.isLookingUp()) {
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
		}
		else {
			setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
		}
	}

	void PlayerStateStanding::exitState()
	{

	}

	void PlayerStateStanding::initAnimation()
	{
		_animUpperStandIdle.init("Tarma_Normal_Pistol_Upper_StandIdle");
		_animLowerStandIdle.init("Tarma_Normal_Pistol_Lower_StandIdle");
		_animUpperStandFire.init("Tarma_Normal_Pistol_Upper_StandFire");
		_animAllStandKnifing[0].init("Tarma_Normal_Pistol_Upper_StandKnifeA");
		_animAllStandKnifing[1].init("Tarma_Normal_Pistol_Upper_StandKnifeB");
		_animUpperStandGrenade.init("Tarma_Normal_Pistol_Upper_StandGrenade");

		_animUpperWatchUpIdle.init("Tarma_Normal_Pistol_Upper_WatchUpIdle");
		_animUpperWatchUpFire.init("Tarma_Normal_Pistol_Upper_WatchUpFire");

		_animAllTurn.init("Tarma_Normal_Pistol_All_Turn");
		_animUpperToWatchUp.init("Tarma_Normal_Pistol_Upper_ToWatchUp");
		_animUpperFromWatchUp.init("Tarma_Normal_Pistol_Upper_FromWatchUp");

		_animUpperFunMotion[0].init("Tarma_Normal_Pistol_Upper_FunMotionDrink");
		_animUpperFunMotion[1].init("Tarma_Normal_Pistol_Upper_FunMotionSleep");
		_animReload.init("Tarma_Normal_Pistol_Upper_StandReload");
		_animAllBrake.init("Tarma_Normal_Pistol_All_Brake");
	}


	void PlayerStateStanding::stateUpdate()
	{
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SPACE)) {
			if (_player.isLookingUp()) {
				setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
			}
			else {
				if (_player.isLookingLeft()) {
					if (_player.isLeftKnifeTriggerOn()) {
						setUpperAnimation(_animAllStandKnifing[_knifeIdx].get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
						_subState = KNIFE;
						_knifeIdx++;
					}
					else {
						setUpperAnimation(_animUpperStandFire.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
						_subState = FIRING;
					}
				}
				else {
					if (_player.isRightKnifeTriggerOn()) {
						setUpperAnimation(_animAllStandKnifing[_knifeIdx].get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
						_subState = KNIFE;
						_knifeIdx++;
					}
					else {
						setUpperAnimation(_animUpperStandFire.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
						_subState = FIRING;
					}
				}
				if (_knifeIdx == 2) {
					_knifeIdx = 0;
				}
			}

		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			setUpperAnimation(_animUpperStandGrenade.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
			_subState = GRENADE;
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_LSHIFT)) {
			//점프
			_player.setPlayerState(_player.getPlayerState(PlayerStates::JUMPING));
			return;
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			//왼쪽으로 돌기
			if (_player.isLookingLeft() == false) {
				setUpperAnimation(_animAllTurn.get(false));
				setLowerAnimation(NULL);
				_player.setLookingLeft(true);
				_subState = TURNING;
			}
			else {
				//걷기 시작
				_player.setPlayerState(_player.getPlayerState(PlayerStates::WALKING));
				return;
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			//오른쪽으로 돌기
			if (_player.isLookingLeft() == true) {
				setUpperAnimation(_animAllTurn.get(true));
				setLowerAnimation(NULL);
				_player.setLookingLeft(false);
				_subState = TURNING;
			}
			else {
				//걷기 시작
				_player.setPlayerState(_player.getPlayerState(PlayerStates::WALKING));
				return;
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			if (_player.isLookingUp() == false) {
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				_player.setLookingUp(true);
				_subState = LIFTING_HEAD;
			}
		}
		else {
			if (_player.isLookingUp()) {
				setUpperAnimation(_animUpperFromWatchUp.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
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
		case TURNING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case LIFTING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
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
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandFire.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
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
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case KNIFE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.isLookingUp()) {
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				else {
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				_subState = IDLE;
			}
		}
		break;
		case FUNMOTION:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				_subState = IDLE;
			}
		}
		break;
		}
	}

}