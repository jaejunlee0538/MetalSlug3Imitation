#include "BulletIface.h"
#include "CollisionComponentCircle.h"
#include "CommonMacroHeader.h"
#include "CollisionConfig.h"
#include <algorithm>
#include "WorldClock.h"
#include "LayerManager.h"
namespace SGA {
	BulletIface::BulletIface(CollisionLayers collisionLayer)
	{
		_bulletCollider = new CollisionComponentCircle(*this, makeRectCenter<RECT, int>(0, 0, 10, 10), true, collisionLayer);
		setCollisionComponent(_bulletCollider);
		setInactive();
		_isLifeTimeEnabled = false;
		_splashDamageCollider = NULL;
		_currrentAnim = NULL;
		_layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_FOREGROUND);
		disableGravity();
	}

	void BulletIface::render()
	{
		if (_currrentAnim) {
			_layer->renderInWrold(_currrentAnim, getPosition().x, getPosition().y);
		}
	}

	void BulletIface::update()
	{
		if (_currrentAnim) {
			_currrentAnim->update();
		}
		if (_beingDestroied) {
			if (_currrentAnim) {
				if (_currrentAnim->getPlayCount() == 1) {
					setInactive();
					return;
				}
			}
			else {
				setInactive();
				return;
			}
		}
		else {
			bulletMotionUpdate();
			if (_isLifeTimeEnabled && _beingDestroied == false) {
				_liveTimeAccum += GET_GAME_WORLD_CLOCK()->getDeltaTimeMillis();
				if (_liveTimeAccum >= _lifeTime) {
					destroy();
				}
			}
		}
	}

	void BulletIface::onCollidingEnter(GameObject & other)
	{
		if (std::any_of(_targetObjTypes.begin(),
			_targetObjTypes.end(),
			[&other](GameObjectTypes& type) {return type == other.getTypeID(); })) {
			onHitTarget(other);
		}

		//스플래시 데미지 
		if (_beingDestroied && _splashDamageCollider) {
			if (std::find(_targetObjTypes.begin(), _targetObjTypes.end(), other.getTypeID()) 
				!= _targetObjTypes.end()) {
				onSplashHitTarget(other);
			}
		}
	}

	void BulletIface::enableLifeTime(DWORD lifeTime)
	{
		_isLifeTimeEnabled = true;
		_lifeTime = lifeTime;
	}

	void BulletIface::enableSplashDamage(int w, int h, int offsetX, int offsetY) {
		//TODO:
	}

	void BulletIface::fire()
	{
		onFire();
		_collidable = true;
		setCollisionComponent(_bulletCollider);
		setActive();
		_beingDestroied = false;
	}

	void BulletIface::destroy()
	{
		onDestroied();
		
		_beingDestroied = true;
		if (_splashDamageCollider) {
			setCollisionComponent(_splashDamageCollider);
		}
		else {
			_collidable = false;
			//setCollisionComponent(NULL);
		}
	}

	void BulletIface::setCollisionLayer(CollisionLayers collisionLayer)
	{
		_bulletCollider->setCollisionLayer(collisionLayer);
	}

	void BulletIface::setTargetObjectTypes(const std::vector<GameObjectTypes>& targetObjTypes)
	{
		_targetObjTypes = targetObjTypes;
	}

	void BulletIface::setBulletRadius(int radius)
	{
		_bulletCollider->setRECT(makeRectCenter<RECT, int>(0, 0, 2 * radius, 2 * radius));
	}
}