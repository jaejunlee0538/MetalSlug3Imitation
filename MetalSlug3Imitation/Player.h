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

		template <typename PlayerStateT>
		PlayerStateT* getPlayerState(PlayerStates state) {
			PlayerStateIface::PlayerStateMap::iterator it = _stateMap.find(state);
			assert(it != _stateMap.end());
			return dynamic_cast<PlayerStateT*>(it->second);
		}

		void setPlayerState(PlayerStateIface* currentState) {
			if (_currentState) {
				_currentState->exitState();
			}
			_currentState = currentState;
			_currentState->enterState();
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
	protected:
		CollisionTriggerBox * _groundCheckBox;
		CollisionTriggerBox* _rightKnifeTrigger;
		CollisionTriggerBox* _leftKnifeTrigger;

		SpritesAnimation* _tarmaRight[2];
		SpritesAnimation* _tarmaLeft[2];

		PlayerStateIface::PlayerStateMap _stateMap;
		PlayerStateIface* _currentState;
		bool _lookingLeft;
		bool _lookingUp;
		Layer* _layer;
	};
}