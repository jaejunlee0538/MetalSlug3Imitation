#pragma once
#include <GameObject.h>
#include "CollisionTriggerBox.h"
#include <SpritesAnimation.h>
#include <Sprite.h>
#include <map>
#include "PlayerStateIface.h"
#include <Layer.h>
namespace SGA {
	class Player :
		public GameObject
	{
	public:
		Player();
		virtual ~Player();

		std::string getTag() const {
			return "Player";
		}

		virtual void movePosition(float dx, float dy) {
			GameObject::movePosition(dx, dy);
		}
		virtual void setPosition(float x, float y) {
			GameObject::setPosition(x,y);
		}

		void update();

		void render();

		bool isRenderable() const {
			return true;
		}

		Layer* getRenderLayer() {
			return _layer;
		}

		int getCloseAttackDamage() const {
			return 100;
		}

		PlayerStateIface* getPlayerState(PlayerStates state) {
			PlayerStateIface::PlayerStateMap::iterator it = _stateMap.find(state);
			assert(it != _stateMap.end());
			return it->second;
		}

		void setPlayerState(PlayerStateIface* currentState) {
			if (_currentState) {
				_currentState->exitState();
			}
			currentState->enterState(_currentState);
			_currentState = currentState;
		}

		inline void setLookingUp(bool lookingUp) {
			_lookingUp = lookingUp;
		}

		inline bool isLookingUp() const {
			return _lookingUp;
		}

		inline void setLookingLeft(bool lookingLeft) {
			_lookingLeft = lookingLeft;
		}

		inline bool isLookingLeft() const {
			return _lookingLeft;
		}

		inline bool isLeftKnifeTriggerOn() const {
			return _leftKnifeTrigger->isCollisionTriggered();
		}

		inline bool isRightKnifeTriggerOn() const {
			return _rightKnifeTrigger->isCollisionTriggered();
		}

		inline bool isGrounded() const {
			return _groundCheckBox->isCollisionTriggered();
		}

		void setUpperAnimation(SpritesAnimation* animUpper) {
			_animUpper = animUpper;
		}
		void setLowerAnimation(SpritesAnimation* animLower) {
			_animLower = animLower;
		}
		SpritesAnimation* getUpperAnimation() {
			return _animUpper;
		}
		SpritesAnimation* getLowerAnimation() {
			return _animLower;
		}
		
	protected:
		CollisionTriggerBox * _groundCheckBox;
		CollisionTriggerBox* _rightKnifeTrigger;
		CollisionTriggerBox* _leftKnifeTrigger;

		SpritesAnimation* _animUpper;
		SpritesAnimation* _animLower;

		PlayerStateIface::PlayerStateMap _stateMap;
		PlayerStateIface* _currentState;
		bool _lookingLeft;
		bool _lookingUp;
		Layer* _layer;
	};
}