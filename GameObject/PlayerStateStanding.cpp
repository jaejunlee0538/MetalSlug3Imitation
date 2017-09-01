#include "PlayerStateStanding.h"
#include "AnimationManager.h"
#include "KeyManager.h"
#include "Player.h"
#include "RandomFunction.h"
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
		processKeyInput();
		//애니메이션이 다른 스테이트 객체로 전달될 수도 있기 대문에 update는 Player가 직접 호출하자.
		stateUpdate();
	}

	void PlayerStateStanding::enterState(PlayerStateIface * prev)
	{
		_subState = IDLE;
		switch (_player.getPlayerActionDir()) {
		case PlayerActionDir::FRONT:
			setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::UP:
			setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
			setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
			break;
		case PlayerActionDir::DOWN:
			setUpperAnimation(_animKneeIdle.get(_player.isLookingLeft()));
			setLowerAnimation(NULL);
			break;
		}
	}

	void PlayerStateStanding::exitState()
	{

	}

	void PlayerStateStanding::initAnimation()
	{
		_animUpperStandIdle.init("Tarma_Normal_Pistol_Upper_StandIdle");
		_animLowerStandIdle.init("Tarma_Normal_Pistol_Lower_StandIdle");
		_animAllTurn.init("Tarma_Normal_Pistol_All_Turn");
		_animUpperStandFire.init("Tarma_Normal_Pistol_Upper_StandFire");
		_animUpperStandKnifing[0].init("Tarma_Normal_Pistol_Upper_StandKnifeA");
		_animUpperStandKnifing[1].init("Tarma_Normal_Pistol_Upper_StandKnifeB");
		_animUpperStandGrenade.init("Tarma_Normal_Pistol_Upper_StandGrenade");

		_animUpperWatchUpIdle.init("Tarma_Normal_Pistol_Upper_WatchUpIdle");
		_animUpperWatchUpFire.init("Tarma_Normal_Pistol_Upper_WatchUpFire");
		_animAllWatchUpTurn.init("Tarma_Normal_Pistol_All_WatchUpTurn");
		_animUpperToWatchUp.init("Tarma_Normal_Pistol_Upper_ToWatchUp");
		_animUpperFromWatchUp.init("Tarma_Normal_Pistol_Upper_FromWatchUp");

		_animKneeIdle.init("Tarma_Normal_Pistol_All_KneeIdle");
		_animAllKneeTurn.init("Tarma_Normal_Pistol_All_KneeTurn");
		_animToKnee.init("Tarma_Normal_Pistol_All_ToKnee");
		_animFromKnee.init("Tarma_Normal_Pistol_All_FromKnee");
		_animKneeIdleAfterGrenade.init("Tarma_Normal_Pistol_All_KneeAfterGrenade");
		_animKneeFire.init("Tarma_Normal_Pistol_All_KneeFire");
		_animKneeGrenade.init("Tarma_Normal_Pistol_All_KneeGrenade");
		_animKneeKnife[0].init("Tarma_Normal_Pistol_All_KneeKnifeA");
		_animKneeKnife[1].init("Tarma_Normal_Pistol_All_KneeKnifeB");

		_animAllBrake.init("Tarma_Normal_Pistol_All_Brake");
		_animUpperFunMotion[0].init("Tarma_Normal_Pistol_Upper_FunMotionDrink");
		_animUpperFunMotion[1].init("Tarma_Normal_Pistol_Upper_FunMotionSleep");
		_animReload.init("Tarma_Normal_Pistol_Upper_StandReload");
	}

	void PlayerStateStanding::stateUpdate()
	{
		switch (_subState) {
		case IDLE:
		{

		}
		break;
		case TURNING:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animKneeIdle.get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
				}
				break;
				}
			}
		}
		break;
		case LIFTING_HEAD:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
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
				if (_player.getUpperAnimation()->getPlayCount() == 1) {
					switch (_player.getPlayerActionDir()) {
					case PlayerActionDir::FRONT:
					{
						setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::UP:
					{
						setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::DOWN:
					{
						setUpperAnimation(_animKneeIdle.get(_player.isLookingLeft()));
						setLowerAnimation(NULL);
					}
					break;
					}
				}
				_subState = IDLE;
			}
		}
		break;
		case GRENADE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.getUpperAnimation()->getPlayCount() == 1) {
					switch (_player.getPlayerActionDir()) {
					case PlayerActionDir::FRONT:
					{
						setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::UP:
					{
						setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::DOWN:
					{
						setUpperAnimation(_animKneeIdleAfterGrenade.get(_player.isLookingLeft()));
						setLowerAnimation(NULL);
					}
					break;
					}
				}
				_subState = IDLE;
			}
		}
		break;
		case KNIFE:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				if (_player.getUpperAnimation()->getPlayCount() == 1) {
					switch (_player.getPlayerActionDir()) {
					case PlayerActionDir::FRONT:
					{
						setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::UP:
					{
						setUpperAnimation(_animUpperWatchUpIdle.get(_player.isLookingLeft()));
						setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					}
					break;
					case PlayerActionDir::DOWN:
					{
						setUpperAnimation(_animKneeIdle.get(_player.isLookingLeft()));
						setLowerAnimation(NULL);
					}
					break;
					}
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
		case KNEEING_DOWN:
		{
			if (_player.getUpperAnimation()->getPlayCount() == 1) {
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animUpperStandIdle.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
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

	void PlayerStateStanding::processKeyInput()
	{
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SPACE)) {
			
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
			{
				if ((_player.isLookingLeft() && _player.isLeftKnifeTriggerOn())
					|| (_player.isLookingLeft() == false && _player.isRightKnifeTriggerOn())) {
					setUpperAnimation(_animUpperStandKnifing[_knifeIdx].get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					_subState = KNIFE;
					_knifeIdx++;
					if (_knifeIdx == 2) {
						_knifeIdx = 0;
					}
				}
				else {
					setUpperAnimation(_animUpperStandFire.get(_player.isLookingLeft()));
					setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
					_subState = FIRING;
					fire();
				}
			}
			break;
			case PlayerActionDir::UP:
			{
				setUpperAnimation(_animUpperWatchUpFire.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				_subState = FIRING;
				fire();
			}
			break;
			case PlayerActionDir::DOWN:
			{
				if ((_player.isLookingLeft() && _player.isLeftKnifeTriggerOn())
					|| (_player.isLookingLeft() == false && _player.isRightKnifeTriggerOn())) {
					setUpperAnimation(_animKneeKnife[_knifeIdx].get(_player.isLookingLeft()));
					setLowerAnimation(NULL);
					_subState = KNIFE;
					_knifeIdx++;
					if (_knifeIdx == 2) {
						_knifeIdx = 0;
					}
				}
				else {
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
			{
				setUpperAnimation(_animUpperStandGrenade.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
			}
			break;
			case PlayerActionDir::DOWN:
			{
				setUpperAnimation(_animKneeGrenade.get(_player.isLookingLeft()));
				setLowerAnimation(NULL);
			}
			break;
			}
			_subState = GRENADE;
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_LSHIFT)) {
			//점프
			_player.setPlayerState(_player.getPlayerState(PlayerStates::JUMPING));
			return;
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			if (_player.isLookingLeft() == false) {
				//왼쪽으로 돌기
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animAllTurn.get(false));
					setLowerAnimation(NULL);
					_player.setLookingLeft(true);
					_subState = TURNING;
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animAllWatchUpTurn.get(false));
					setLowerAnimation(NULL);
					_player.setLookingLeft(true);
					_subState = TURNING;
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animAllKneeTurn.get(false));
					setLowerAnimation(NULL);
					_player.setLookingLeft(true);
					_subState = IDLE;
				}
				break;
				}
			}
			else {
				//걷기 시작
				_player.setPlayerState(_player.getPlayerState(PlayerStates::WALKING));
				return;
			}
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			if (_player.isLookingLeft() == true) {
				//오른쪽으로 돌기
				switch (_player.getPlayerActionDir()) {
				case PlayerActionDir::FRONT:
				{
					setUpperAnimation(_animAllTurn.get(true));
					setLowerAnimation(NULL);
					_player.setLookingLeft(false);
					_subState = TURNING;
				}
				break;
				case PlayerActionDir::UP:
				{
					setUpperAnimation(_animAllWatchUpTurn.get(true));
					setLowerAnimation(NULL);
					_player.setLookingLeft(false);
					_subState = TURNING;
				}
				break;
				case PlayerActionDir::DOWN:
				{
					setUpperAnimation(_animAllKneeTurn.get(true));
					setLowerAnimation(NULL);
					_player.setLookingLeft(false);
					_subState = IDLE;
				}
				break;
				}
			}
			else {
				//걷기 시작
				_player.setPlayerState(_player.getPlayerState(PlayerStates::WALKING));
				return;
			}
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
			{
				setUpperAnimation(_animUpperToWatchUp.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::UP);
				_subState = LIFTING_HEAD;
			}
			break;
			}
		}
		else {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::UP:
			{
				setUpperAnimation(_animUpperFromWatchUp.get(_player.isLookingLeft()));
				setLowerAnimation(_animLowerStandIdle.get(_player.isLookingLeft()));
				_player.setPlayerActionDir(PlayerActionDir::FRONT);
				_subState = LIFTING_HEAD;
			}
			break;
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::FRONT:
			{
				setUpperAnimation(_animToKnee.get(_player.isLookingLeft()));
				setLowerAnimation(NULL);
				_player.setPlayerActionDir(PlayerActionDir::DOWN);
				_subState = KNEEING_DOWN;
			}
			break;
			}
		}
		else {
			switch (_player.getPlayerActionDir()) {
			case PlayerActionDir::DOWN:
			{
				setUpperAnimation(_animFromKnee.get(_player.isLookingLeft()));
				setLowerAnimation(NULL);
				_player.setPlayerActionDir(PlayerActionDir::FRONT);
				_subState = KNEEING_DOWN;
			}
			break;
			}
		}
	}

	void PlayerStateStanding::fire()
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
				pos.x+= 5;
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