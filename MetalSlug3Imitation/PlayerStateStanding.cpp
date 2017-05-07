#include "PlayerStateStanding.h"
#include <AnimationManager.h>
#include <KeyManager.h>
#include "Player.h"
#include <RandomFunction.h>
namespace SGA {
	PlayerStateStanding::PlayerStateStanding(Player & player)
		:PlayerStateIface(player), _funMotionTimeout(GET_GAME_WORLD_CLOCK(), 5000){
		findAnimation();
		_knifeIdx = 0;
	}

	PlayerStateStanding::~PlayerStateStanding()
	{

	}

	void PlayerStateStanding::update()
	{
		_currentAnimation->update();
		stateUpdate();
		processKeyinput();
	}

	void PlayerStateStanding::render()
	{
		POINTFLOAT pos = _player.getPosition();
		_player.getRenderLayer()->renderInWrold(_currentAnimation, pos.x, pos.y);
	}

	void PlayerStateStanding::enterState()
	{
		_subState = Substate::NONE;
		bool left = _player.isLookingLeft();
		bool lookUp = _player.isLookingUp();
		if (left) {
			if (lookUp) {
				setAnimation(_animationWatchingUpLeft);
				setSubstate(Substate::NONE);
			}
			else {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);
			}
		}
		else {
			if (lookUp) {
				setAnimation(_animationWatchingUpRight);
				setSubstate(Substate::NONE);
			}
			else {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
	}

	void PlayerStateStanding::exitState()
	{

	}

	void PlayerStateStanding::setSubstate(Substate substate)
	{
		_funMotionTimeout.reset();
		_subState = substate;
	}

	void PlayerStateStanding::findAnimation()
	{
		_animationWatchingUpRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandWatchUp_Right");
		_animationWatchingUpLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandWatchUp_Left");

		_animationToWatchingUpRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_ToStandWatchUp_Right");
		_animationToWatchingUpLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_ToStandWatchUp_Left");

		_animationStandingRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandIdle_Right");
		_animationStandingLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandIdle_Left");

		_animationFiringRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandFire_Right");
		_animationFiringLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandFire_Left");

		_animationFiringUpRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandFireUp_Right");
		_animationFiringUpLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandFireUp_Left");

		_animationKnifingRight[0] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandKnifeA_Right");
		_animationKnifingLeft[0] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandKnifeA_Left");
		_animationKnifingRight[1] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandKnifeB_Right");
		_animationKnifingLeft[1] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandKnifeB_Left");

		_animationGrenadeRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandGrenade_Right");
		_animationGrenadeLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandGrenade_Left");

		_animationFunMotionRight[0] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_FunmotionA_Right");
		_animationFunMotionLeft[0] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_FunmotionA_Left");

		_animationFunMotionRight[1] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_FunmotionB_Right");
		_animationFunMotionLeft[1] = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_FunmotionB_Left");

		_animationTurningRight = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandTurnLeft_Right");
		_animationTurningLeft = GET_ANIMATION_MANAGER()->findAnimation("Tarma_Normal_Pistol_StandTurnLeft_Left");;
	}
	void PlayerStateStanding::processKeyinput()
	{
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			if (_player.isLookingLeft()) {
				//¿ÞÂÊÀ¸·Î ÀÌµ¿
			}
			else {
				_player.setLookingLeft(true);
				setSubstate(Substate::TURNING_LEFT);
				setAnimation(_animationTurningLeft);
			}
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			if (_player.isLookingLeft()) {
				_player.setLookingLeft(false);
				setSubstate(Substate::TURNING_RIGHT);
				setAnimation(_animationTurningRight);
			}
			else {
				//¿À¸¥ÂÊÀ¸·Î °È±â ½ÃÀÛ
			}
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_DOWN)) {
			//__¹«¸­ ²Ý±â
		}
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			//__À§ ÃÄ´Ùº¸±â
			if (_player.isLookingUp() == false) {
				_player.setLookingUp(true);
				if (_player.isLookingLeft()) {
					setAnimation(_animationToWatchingUpLeft);
					setSubstate(Substate::TO_WATCHUP_LEFT);
				}
				else {
					setAnimation(_animationToWatchingUpRight);
					setSubstate(Substate::TO_WATCHUP_RIGHT);
				}
			}
		}
		else {
			if (_player.isLookingUp()) {
				_player.setLookingUp(false);
				if (_player.isLookingLeft()) {
					setAnimation(_animationStandingLeft);
					setSubstate(Substate::NONE);
				}
				else {
					setAnimation(_animationStandingRight);
					setSubstate(Substate::NONE);
				}
			}
		}

		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_CONTROL)) {
			//¼ö·ùÅº
			if (_player.isLookingLeft()) {
				setSubstate(Substate::THROWING_GRENADE_LEFT);
				setAnimation(_animationGrenadeLeft);
			}
			else {
				setSubstate(Substate::THROWING_GRENADE_RIGHT);
				setAnimation(_animationGrenadeRight);
			}
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_LSHIFT)) {
			//Á¡ÇÁ
		}
		if (GET_KEY_MANAGER()->isOnceKeyDown(VK_SPACE)) {
			//ÃÑ½î±â
			if (_player.isLookingUp()) {
				if (_player.isLookingLeft()) {
					setSubstate(Substate::FIRING_UP_LEFT);
					setAnimation(_animationFiringUpLeft);
				}
				else {
					setSubstate(Substate::FIRING_UP_RIGHT);
					setAnimation(_animationFiringUpRight);
				}
			}
			else {
				if (_player.isLookingLeft()) {
					if (!_player.isLeftKnifeTriggerOn()) {
						if (_subState != Substate::KNIFING_LEFT) {
							setSubstate(Substate::KNIFING_LEFT);
							setAnimation(_animationKnifingLeft[_knifeIdx++]);
						}
					}
					else {
						setSubstate(Substate::FIRING_LEFT);
						setAnimation(_animationFiringLeft);
					}
				}
				else {
					if (!_player.isRightKnifeTriggerOn()) {
						if (_subState != Substate::KNIFING_RIGHT) {
							setSubstate(Substate::KNIFING_RIGHT);
							setAnimation(_animationKnifingRight[_knifeIdx++]);
						}
					}
					else {
						setSubstate(Substate::FIRING_RIGHT);
						setAnimation(_animationFiringRight);
					}
				}
			}

		}
		if (_knifeIdx == 2) {
			_knifeIdx = 0;
		}
	}
	void PlayerStateStanding::setAnimation(SpritesAnimation * newAnimation)
	{
		_currentAnimation = newAnimation;
		_currentAnimation->restart();
	}
	void PlayerStateStanding::stateUpdate()
	{
		switch (_subState) {
		case Substate::TO_WATCHUP_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationWatchingUpLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::TO_WATCHUP_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationWatchingUpRight);
				setSubstate(Substate::NONE);

			}
		}
		break;
		case Substate::TURNING_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);

			}
		}
		break;
		case Substate::TURNING_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::THROWING_GRENADE_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::THROWING_GRENADE_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FIRING_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FIRING_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FIRING_UP_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationWatchingUpLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FIRING_UP_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationWatchingUpRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::KNIFING_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::KNIFING_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FUNMOTION_RIGHT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingRight);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::FUNMOTION_LEFT:
		{
			if (_currentAnimation->getPlayCount() == 1) {
				setAnimation(_animationStandingLeft);
				setSubstate(Substate::NONE);
			}
		}
		break;
		case Substate::NONE:
		{
			if (_funMotionTimeout.isTimeout()) {
				if (_player.isLookingUp() == false) {
					int idx = GET_RANDOM_FUNCTION()->getInt(1);
					if (_player.isLookingLeft()) {
						setAnimation(_animationFunMotionLeft[idx]);
						setSubstate(Substate::FUNMOTION_LEFT);
					}
					else {
						setAnimation(_animationFunMotionRight[idx]);
						setSubstate(Substate::FUNMOTION_RIGHT);
					}
				}
				
			}
		}
			break;
		}
	}
}