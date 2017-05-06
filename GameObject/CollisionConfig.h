#pragma once
#include "CollisionComponent.h"


#define COLLISION_LAYER_GROUND			SGA::COLLISION_LAYER1
#define COLLISION_LAYER_STRUCTURE		SGA::COLLISION_LAYER2
#define COLLISION_LAYER_PLAYER_BULLET	SGA::COLLISION_LAYER3
#define COLLISION_LAYER_ENEMY_BULLET	SGA::COLLISION_LAYER4
#define COLLISION_LAYER_TRIGGER_BOX		SGA::COLLISION_LAYER5
#define COLLISION_LAYER_ENEMY_BODY		SGA::COLLISION_LAYER6
#define COLLISION_LAYER_PLAYER_BODY		SGA::COLLISION_LAYER7
#define COLLISION_LAYER_GENERAL			SGA::COLLISION_LAYER8


void initCollisionLayer();