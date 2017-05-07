#include "CollisionConfig.h"



void initCollisionLayer()
{
	SGA::CollisionComponent::disableCollisionsBetweenAllLayers();
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_GROUND, COLLISION_LAYER_ENEMY_BODY);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_GROUND, COLLISION_LAYER_ENEMY_BULLET);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_GROUND, COLLISION_LAYER_PLAYER_BODY);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_GROUND, COLLISION_LAYER_PLAYER_BULLET);
	
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_TRIGGER_BOX, COLLISION_LAYER_GROUND);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_TRIGGER_BOX, COLLISION_LAYER_PLAYER_BODY);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_TRIGGER_BOX, COLLISION_LAYER_ENEMY_BODY);

	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BULLET, COLLISION_LAYER_ENEMY_BODY);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BULLET, COLLISION_LAYER_ENEMY_BULLET);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BULLET, COLLISION_LAYER_STRUCTURE);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BULLET, COLLISION_LAYER_GENERAL);

	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BODY, COLLISION_LAYER_ENEMY_BULLET);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_PLAYER_BODY, COLLISION_LAYER_GENERAL);

	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_ENEMY_BODY, COLLISION_LAYER_GENERAL);
	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_ENEMY_BODY, COLLISION_LAYER_STRUCTURE);

	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_STRUCTURE, COLLISION_LAYER_ENEMY_BULLET);

	SGA::CollisionComponent::enableCollisionBetweenLayers(COLLISION_LAYER_GENERAL, COLLISION_LAYER_ENEMY_BULLET);
}