#include "Player.h"
#include "WalkerFootCircle.h"
#include <AnimationManager.h>
#include <SpriteManager.h>
#include <KeyManager.h>
#include <LayerManager.h>
#include <Camera.h>
#include <CollisionComponentRectangle.h>
#include <CommonMacroHeader.h>
#include "Stdafx.h"
#include <CollisionConfig.h>
namespace SGA {
	Player::Player()
	{
		//disableGravity();
		WalkerFootCircle* footCircle = new WalkerFootCircle(0, 11, 7);
		_groundCheckBox = new CollisionTriggerBox(0,18,17,4);

		_rightKnifeTrigger	= new CollisionTriggerBox(10, -3,21,14);
		_leftKnifeTrigger = new CollisionTriggerBox(-10, -3, 21, 14);

		CollisionComponentRectangle *body = new CollisionComponentRectangle(*this,
			SGA::makeRectCenter<RECT, int>(0, 0, 10, 30), false, COLLISION_LAYER_PLAYER_BODY);
		setCollisionComponent(body);
		addChild(footCircle);
		addChild(_groundCheckBox);
		addChild(_leftKnifeTrigger);
		addChild(_rightKnifeTrigger);

		_tarmaRight[0] = GET_SPRITE_MANAGER()->findSprite("Tarma/Pistol/UpperStandStill_0");
		_tarmaRight[1] = GET_SPRITE_MANAGER()->findSprite("Tarma/Pistol/LowerStandStill_0");
		_tarmaLeft[0] = GET_SPRITE_MANAGER()->findSprite("Tarma/Pistol/UpperStandStill_0_mirror");
		_tarmaLeft[1] = GET_SPRITE_MANAGER()->findSprite("Tarma/Pistol/LowerStandStill_0_mirror");
		_left = false;
	/*	_tarmaWalkingRightUpper = GET_ANIMATION_MANAGER()->findAnimation("JumpingStayStill_UpperRight");
		_tarmaWalkingRightLower = GET_ANIMATION_MANAGER()->findAnimation("JumpingStayStill_LowerRight");

		_tarmaWalkingLeftUpper = GET_ANIMATION_MANAGER()->findAnimation("JumpingStayStill_UpperLeft");
		_tarmaWalkingLeftLower = GET_ANIMATION_MANAGER()->findAnimation("JumpingStayStill_LowerLeft");*/


	}

	Player::~Player()
	{
	}

	void Player::update() {
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			_left = true;
			movePosition(-4, 0);
		}
		
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			_left = false;
			movePosition(4, 0);
		}

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
		Layer* layer = GET_LAYER_MANAGER()->findLayer(SGA::LayerManager::LAYER_INDEX_GAME_OBJECT);
		if (_left) {
			layer->renderInWrold(_tarmaLeft[0], getPosition().x, getPosition().y);
			layer->renderInWrold(_tarmaLeft[1], getPosition().x, getPosition().y);
		}
		else {
			layer->renderInWrold(_tarmaRight[0], getPosition().x, getPosition().y);
			layer->renderInWrold(_tarmaRight[1], getPosition().x, getPosition().y);
		}
	}
}