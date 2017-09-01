#include "PlayerStateWalking.h"
#include "AnimationManager.h"
#include "Player.h"
#include "KeyManager.h"
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
		processKeyInput();
		updateState();
		moveUpdate();
	}

	void PlayerStateWalking::render()
	{

	}

	void PlayerStateWalking::enterState(PlayerStateIface* prev)
	{
		_subState = IDLE;
		switch (_player.getPlayerActionDir()) {
		case PlayerActionDir::FRONT:
			setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerWalk.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::UP:
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerWalk.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::DOWN:
			setUpperAnimation(_animKneeWalk.get(_player.isLookingLeft()));
			setLowerAnimation(NULL);
			break;
		}
	}

	void PlayerStateWalking::exitState()
	{
	}
	void PlayerStateWalking::updateState()
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
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
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
		case FIRING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animKneeWalk.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
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
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animKneeWalk.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
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
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animKneeWalk.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
				}
				break;
				}
			}
			_subState = IDLE;

		}
		break;
		case KNEEING_DOWN:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperWalk.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerWalk.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animKneeIdle.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
				}
				break;
				}
				_subState = IDLE;
			}
		}
		break;
		}
	}

	void PlayerStateWalking::moveUpdate()
	{
		if (_player.getPlayerActionDir() == PlayerActionDir::DOWN) {
			if (_subState == IDLE) {
				if (_player.isLookingLeft()) {
					_player.movePosition(-2, 0);
				}
				else {
					_player.movePosition(2, 0);
				}
			}
		}
		else {
			if (_player.isLookingLeft()) {
				_player.movePosition(-4, 0);
			}
			else {
				_player.movePosition(4, 0);
			}
		}
	}
	void PlayerStateWalking::processKeyInput()
	{
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
				if ((_player.isLookingLeft() && _player.isLeftKnifeTriggerOn())
					|| (_player.isLookingLeft() == false && _player.isRightKnifeTriggerOn())) {
					//정면에 나이프 공격
					setUpperAnimation(_animKneeKnife[_knifeIdx].get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
					_subState = KNIFE;
					_knifeIdx++;
					if (_knifeIdx == 2) {
						_knifeIdx = 0;
					}
				}
				else {
					//정면에 총 발사
					setUpperAnimation(_animKneeFire.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
					_subState = FIRING;
					fire();
				}
			}
			break;
			}
		}

		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:case PlayerActionDir::UP:
				//서있는 상태로 수류탄
				setUpperAnimation(_animUpperGrenade.get(_player.isLookingLeft()));
				break;
			case PlayerActionDir::DOWN:
				//앉은 상태로 수류탄
				setUpperAnimation(_animKneeGrenade.get(_player.isLookingLeft()));
				setLowerAnimation(NULL);
				break;
			}
			_subState = GRENADE;
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SHIFT)) {
			//점프
		}

		if (_player.isLookingLeft()) {
			//방향키에서 손 떼면 STANDING상태로 전환
			if (GET_KEY_MANAGER()->isStayKeyUp(VK_LEFT)) {
				_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
				return;
			}
		}
		else {
			//방향키에서 손 떼면 STANDING상태로 전환
			if (GET_KEY_MANAGER()->isStayKeyUp(VK_RIGHT)) {
				_player.setPlayerState(_player.getPlayerState(PlayerStates::STANDING));
				return;
			}
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::UP);
				_subState = LIFTING_HEAD;
				break;
			case PlayerActionDir::UP:
				//setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
				break;
			case PlayerActionDir::DOWN:
	/*			setUpperAnimation(_animKneeWalk.get(_player.isLookingLeft()));
				setLowerAnimation(NULL);*/
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
			//앉기 시작
			//걷는 도중에 앉지는 못함.
		}
		else {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::DOWN:
				//기어가다가 일어서기 시작
				setUpperAnimation(_animFromKnee.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::FRONT);
				_subState = KNEEING_DOWN;
				break;
			}
		}
	}
	void PlayerStateWalking::initAnimation()
	{
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

		_animKneeWalk.init("Tarma_Normal_Pistol_All_KneeWalk");
		_animKneeIdle.init("Tarma_Normal_Pistol_All_KneeIdle");
		_animAllKneeTurn.init("Tarma_Normal_Pistol_All_KneeTurn");
		_animToKnee.init("Tarma_Normal_Pistol_All_ToKnee");
		_animFromKnee.init("Tarma_Normal_Pistol_All_FromKnee");
		_animKneeIdleAfterGrenade.init("Tarma_Normal_Pistol_All_KneeAfterGrenade");
		_animKneeFire.init("Tarma_Normal_Pistol_All_KneeFire");
		_animKneeGrenade.init("Tarma_Normal_Pistol_All_KneeGrenade");
		_animKneeKnife[0].init("Tarma_Normal_Pistol_All_KneeKnifeA");
		_animKneeKnife[1].init("Tarma_Normal_Pistol_All_KneeKnifeB");
	}

	void PlayerStateWalking::fire()
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
				pos.x -= 25;
				pos.y + 0;
				_player.getCurrentGun()->fire(pos.x, pos.y, -1, 0);
			}
			else {
				pos.x += 25;
				pos.y + 0;
				_player.getCurrentGun()->fire(pos.x, pos.y, 1, 0);
			}
		}
		break;
		}
	}
}