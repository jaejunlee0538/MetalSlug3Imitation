#include "Player.h"
#include "WalkerFootCircle.h"
#include "AnimationManager.h"
#include "SpriteManager.h"
#include "KeyManager.h"
#include "LayerManager.h"
#include "Camera.h"
#include "CollisionComponentRectangle.h"
#include "CommonMacroHeader.h"
#include "CollisionConfig.h"
namespace SGA {
	Player::Player()
		:_currentState(NULL)
	{
		//disableGravity();
		setLookingLeft(false);

		///////////////////////////////////////////////////////////
		WalkerFootCircle* footCircle = new WalkerFootCircle(0, 7, 8);
		_groundCheckBox = new CollisionTriggerBox(0,16,10, 4, "PlayerGNDCheck");
		_rightKnifeTrigger	= new CollisionTriggerBox(10, -3,21,14,"PlayerRightKnife");
		_leftKnifeTrigger = new CollisionTriggerBox(-10, -3, 21, 14,"PlayerLeftKnife");
		CollisionComponentRectangle *body = new CollisionComponentRectangle(*this,
			SGA::makeRectCenter<RECT, int>(0, 0, 10, 30), false, COLLISION_LAYER_PLAYER_BODY);
		setCollisionComponent(body);
		addChild(footCircle);
		addChild(_groundCheckBox);
		addChild(_leftKnifeTrigger);
		addChild(_rightKnifeTrigger);
		///////////////////////////////////////////////////////////
		_layer = GET_LAYER_MANAGER()->findLayer(SGA::LayerManager::LAYER_INDEX_GAME_OBJECT);
		///////////////////////////////////////////////////////////
		setPlayerActionDir(PlayerActionDir::FRONT);
		_stateMap = PlayerStateIface::createPlayerStateMap(*this);
		setPlayerState(_stateMap[PlayerStates::JUMPING]);
		///////////////////////////////////////////////////////////
		_currentGun = &_defaultGun;
		_defaultGun.setActive();
		addChild(_currentGun);
	}

	Player::~Player()
	{
	}

	void Player::update() {
		if (isGrounded()) {
			disableGravity();
			setGravityVelocity({ 0,0 });
		}
		else {
			enableGravity();
		}

		if (_animLower) {
			_animLower->update();
		}
		if (_animUpper) {
			_animUpper->update();
		}

		_currentState->update();

		//플레이어 위치 클램핑
		POINTFLOAT pos = getPosition();
		RECT clamp = GET_CAMERA()->getScreenRECT();
		if (pos.x < clamp.left) {
			pos.x = clamp.left;
		}
		if (pos.x > clamp.right) {
			pos.x = clamp.right;
		}
	}

	void Player::render() {
		//_currentState->render();
		if (_animLower) {
			_layer->renderInWrold(_animLower, getPosition().x, getPosition().y);
		}
		if (_animUpper) {
			_layer->renderInWrold(_animUpper, getPosition().x, getPosition().y);
		}
	}

}