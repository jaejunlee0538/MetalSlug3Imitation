#include "PlayerStateJumping.h"
#include "KeyManager.h"
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
		processKeyInput();
		stateUpdate();
	}

	void PlayerStateJumping::enterState(PlayerStateIface * prev)
	{
		_subState = IDLE;
		_knifeIdx = 0;

		switch (_player.getPlayerActionDir()) {
		case PlayerActionDir::FRONT:
			setUpperAnimation(_animUpperJump.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerJump.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::UP:
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerJump.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::DOWN:
			setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerJump.get(_player.isLookingLeft()));
			break;
		}
		_player.movePosition(0, -10);
		_player.setGravityVelocity({ 0.0f, -150.0f });
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

	void PlayerStateJumping::processKeyInput()
	{
		if (_player.isGrounded()) {
			_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
			return;
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SPACE)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
			{
				if ((_player.isLookingLeft() && _player.isLeftKnifeTriggerOn())
					|| (_player.isLookingLeft() == false && _player.isRightKnifeTriggerOn())) {
					//정면에 나이프 공격
					setUpperAnimation(_animUpperKnife[_knifeIdx].get(_player.isLookingLeft()));
					_subState = KNIFE;
					_knifeIdx++;
					if (_knifeIdx == 2) {
						_knifeIdx = 0;
					}
				}
				else {
					//정면에 총 발사
					setUpperAnimation(_animUpperFire.get(_player.isLookingLeft()));
					_subState = FIRING;
					fire();
				}
			}
			break;
			case PlayerActionDir::UP:
			{
				//총만 발사할 수 있음
				setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
				_subState = FIRING;
				fire();
			}
			break;
			case PlayerActionDir::DOWN:
			{
				//정면에 총 발사
				setUpperAnimation(_animUpperJumpWatchDownFire.get(_player.isLookingLeft()));
				_subState = FIRING;
				fire();
			}
			break;
			}
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			setUpperAnimation(_animUpperJumpGrenade.get(_player.isLookingLeft()));
			_subState = GRENADE;
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			//TODO : 왼쪽으로 이동
			_player.movePosition(-2, 0);
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			//TODO : 오른쪽으로 이동
			_player.movePosition(2, 0);
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::UP);
				_subState = LIFTING_HEAD;
				break;
			}
		}
		else {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::UP:
				setUpperAnimation(_animUpperFromWatchUp.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::FRONT);
				_subState = LIFTING_HEAD;
				break;
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			//아래 쳐다보기
			if (_player.getPlayerActionDir() != PlayerActionDir::DOWN && _player.getPlayerActionDir() != PlayerActionDir::UP) {
				setUpperAnimation(_animUpperToJumpWatchDown.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::DOWN);
				_subState = LOWERING_HEAD;
			}
		}
		else {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::DOWN:
				//다시 정면 쳐다보자
				setUpperAnimation(_animUpperFromJumpWatchDown.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::FRONT);
				_subState = LOWERING_HEAD;
				break;
			}
		}
	}

	void PlayerStateJumping::stateUpdate()
	{
		switch (_subState) {
		case IDLE:
		{

		}
		break;
		case LIFTING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		case LOWERING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		case FIRING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		case GRENADE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		case KNIFE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animUpperJumpWatchDown.get(_player.isLookingLeft()));
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		}
	}
	void PlayerStateJumping::fire()
	{
		POINTFLOAT pos = _player.getPosition();
		switch (_player.getPlayerActionDir()) {
		case PlayerActionDir::FRONT:
		{
			if (_player.isLookingLeft()) {
				pos.x -= 25;
				pos.y -= 10;
				_player.getCurrentGun()->fire(pos.x, pos.y, -1, 0);
			}
			else {
				pos.x += 25;
				pos.y -= 10;
				_player.getCurrentGun()->fire(pos.x, pos.y, 1, 0);
			}
		}
		break;
		case PlayerActionDir::UP:
		{
			pos.y -= 32;
			if (_player.isLookingLeft()) {
				pos.x -= 5;
			}
			else {
				pos.x += 5;
			}
			_player.getCurrentGun()->fire(pos.x, pos.y, 0, -1);
		}
		break;
		case PlayerActionDir::DOWN:
		{
			if (_player.isLookingLeft()) {
				pos.x -= 0;
				pos.y += 15;
				_player.getCurrentGun()->fire(pos.x, pos.y, 0, 1);
			}
			else {
				pos.x += 0;
				pos.y += 15;
				_player.getCurrentGun()->fire(pos.x, pos.y, 0, 1);
			}
		}
		break;
		}
	}
}