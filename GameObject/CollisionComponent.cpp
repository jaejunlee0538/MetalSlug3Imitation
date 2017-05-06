#include "CollisionComponent.h"
#include "GameObject.h"
#include <assert.h>
namespace {
	class CollisionLayerInitializer {
	public:
		CollisionLayerInitializer() {
			SGA::CollisionComponent::enableCollisionsBetweenAllLayers();
		}
	};
	CollisionLayerInitializer initializeCollisionLayer;
}
namespace SGA {

	bool CollisionComponent::_layerInteraction[NUM_COLLISION_LAYER][NUM_COLLISION_LAYER];

	CollisionComponent::CollisionComponent(GameObject & owner, bool isTrigger, CollisionLayers collisionLayer)
		:_owner(owner), _isTrigger(isTrigger), _collisionLayer(collisionLayer)
	{
		setOffset(0, 0);
	}

	void CollisionComponent::setOffset(float offsetX, float offsetY) {
		_offset.x = offsetX;
		_offset.y = offsetY;
	}

	void CollisionComponent::handleCollision(CollisionComponent * other) {
		if (_collisionMemory.find(other) == _collisionMemory.end()) {
			_collisionMemory.insert(other);
			if (other->isTrigger()) {
				_owner.onTrigerringEnter(other->getOwner());
			}
			else {
				_owner.onCollidingEnter(other->getOwner());
			}
		}
		if (other->isTrigger()) {
			_owner.onTrigerring(other->getOwner());
		}
		else {
			_owner.onColliding(other->getOwner());
		}
	}

	void CollisionComponent::handleNoneCollision(CollisionComponent * other) {
		if (_collisionMemory.find(other) != _collisionMemory.end()) {
			_collisionMemory.erase(other);
			if (other->isTrigger()) {
				_owner.onTrigerringExit(other->getOwner());
			}
			else {
				_owner.onCollidingExit(other->getOwner());
			}
		}
	}

	void CollisionComponent::enableCollisionBetweenLayers(CollisionLayers layer1, CollisionLayers layer2)
	{
		_layerInteraction[layer1][layer2] = true;
		_layerInteraction[layer2][layer1] = true;
	}

	void CollisionComponent::disableCollisionBetweenLayers(CollisionLayers layer1, CollisionLayers layer2)
	{
		_layerInteraction[layer1][layer2] = false;
		_layerInteraction[layer2][layer1] = false;
	}

	void CollisionComponent::enableCollisionsBetweenAllLayers()
	{
		for (int i = 0; i < NUM_COLLISION_LAYER; ++i) {
			for (int k = 0; k < NUM_COLLISION_LAYER; ++k) {
				_layerInteraction[i][k] = true;
			}
		}
	}

	void CollisionComponent::disableCollisionsBetweenAllLayers()
	{
		for (int i = 0; i < NUM_COLLISION_LAYER; ++i) {
			for (int k = 0; k < NUM_COLLISION_LAYER; ++k) {
				_layerInteraction[i][k] = false;
			}
		}
	}

	void CollisionComponent::moveCollidingObject(GameObject * object, float dx, float dy)
	{
		assert(object);
		GameObject* prev;
		while (object != NULL) {
			prev = object;
			object = object->getParent();
		}
		prev->movePosition(dx, dy);
	}
}