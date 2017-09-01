#pragma once
#include "GameObject.h"
#include "WalkerFootCircle.h"
#include "CollisionTriggerBox.h"
#include "Layer.h"

namespace SGA {
	class Player;
	class Enemy :
		public GameObject
	{
	public:
		Enemy(std::string tag, int hp, int width, int height, int alertRangeRadius);
		virtual ~Enemy();

		void enableCloseAttack(int width, int height);
		virtual void attacked() = 0;
		virtual void diedByBullet(Player& player, GameObject& bullet) = 0;
		virtual void diedByKnife(Player& player) = 0;
		virtual void onStayJumpTrigger(bool left) = 0;

		virtual void onCollidingEnter(GameObject& other);
		virtual void onTrigerring(GameObject& other);

		virtual void update();

		bool isGrounded() const;

		std::string getTag()const {
			return _tag;
		}

		bool isRenderable() const {
			return true;
		}

		void giveDamage(int damage);

		inline int getCurrentHP() const {
			return _hp;
		}
	protected:
		Layer* _renderLayer;

	private:
		std::string _tag;
		int _hp;

		CollisionTriggerBox* _leftCloseAttackTrigger;
		CollisionTriggerBox* _rightCloseAttackTrigger;
		CollisionTriggerBox* _groundCheckTrigger;
		WalkerFootCircle* _footCircle;
		CollisionComponentRectangle* _bodyCollision;
	};
}