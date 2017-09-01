#pragma once
#include "GameObject.h"
#include "CollisionTriggerBox.h"
#include "SpritesAnimation.h"
#include "Layer.h"
namespace SGA {
	class BulletIface : public GameObject
	{
	public:
		BulletIface(CollisionLayers collisionLayer);

		virtual ~BulletIface() {

		}

		bool isFired() const {
			return isActive();
		}

		virtual void onFire() = 0;
		virtual void bulletMotionUpdate() = 0;
		virtual void onHitTarget(GameObject& other) = 0;
		virtual void onDestroied() = 0;
		virtual void onSplashHitTarget(GameObject& other){}
		virtual bool isCollidable() const {
			return _collidable;
		}
		void fire();
		void destroy();

		bool isRenderable() const {
			return true;
		}
		
		void setCollisionLayer(CollisionLayers collisionLayer);
		void setTargetObjectTypes(const std::vector<GameObjectTypes>& targetObjTypes);
		void setBulletRadius(int radius);
		void setCurrentAnimation(SpritesAnimation* anim) {
			_currrentAnim = anim;
		}

		void enableLifeTime(DWORD lifeTime);
		void enableSplashDamage(int w, int h, int offsetX, int offsetY);
	private:
		void render();
		void update();
		void onCollidingEnter(GameObject& other);
	private:
		bool _collidable;
		bool _isLifeTimeEnabled;
		DWORD _lifeTime;
		DWORD _liveTimeAccum;
		bool _beingDestroied;
		CollisionComponentCircle* _bulletCollider;
		CollisionComponent* _splashDamageCollider;
		std::vector<GameObjectTypes> _targetObjTypes;
		SpritesAnimation* _currrentAnim;
		Layer* _layer;
	};
}