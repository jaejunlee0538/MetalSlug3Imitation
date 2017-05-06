#pragma once
#include <GameObject.h>
#include "CollisionTriggerBox.h"
#include <SpritesAnimation.h>
#include <Sprite.h>
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

		void update();

		void render();

		bool isRenderable() const {
			return true;
		}

	protected:
		CollisionTriggerBox * _groundCheckBox;
		CollisionTriggerBox* _rightKnifeTrigger;
		CollisionTriggerBox* _leftKnifeTrigger;

		const Sprite* _tarmaRight[2];
		const Sprite* _tarmaLeft[2];

		bool _left;

		//const SpritesAnimation* _tarmaWalkingRightUpper;
		//const SpritesAnimation* _tarmaWalkingRightLower;

		//const SpritesAnimation* _tarmaWalkingLeftUpper;
		//const SpritesAnimation* _tarmaWalkingLeftLower;

	};
}