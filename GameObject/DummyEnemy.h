#pragma once
#include "Enemy.h"
namespace SGA {
	class DummyEnemy :
		public Enemy
	{
	public:
		DummyEnemy();
		virtual ~DummyEnemy();
		bool isRenderable() const {
			return true;
		}
		GameObjectTypes getTypeID() const {
			return GameObjectTypes::ENEMY;
		}
		void render();
		virtual void attacked() {
		}
		virtual void diedByBullet(Player& player, GameObject& bullet) {
		}
		virtual void diedByKnife(Player& player) {

		}
		virtual void onStayJumpTrigger(bool left) {

		}
	};

}