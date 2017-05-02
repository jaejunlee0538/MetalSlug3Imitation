#include "PlayerStateStanding.h"
#include "PlayerStateWalking.h"
#include "PlayerStateJumping.h"
#include "Player.h"
#include "Stdafx.h"
#include "Sprite.h"

PlayerStateStanding::PlayerStateStanding()
{

}

PlayerStateStanding::~PlayerStateStanding()
{
}

void PlayerStateStanding::enter(Player & player)
{
	std::vector<const SGA::Sprite*> upperSprites, lowerSprites;

	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperStandStill_0"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperStandStill_1"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperStandStill_2"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperStandStill_3"));

	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerStandStill_0"));

	SpritesAnimation * upperAnimation = new SpritesAnimation(upperSprites, 300);
	SpritesAnimation * lowerAnimation = new SpritesAnimation(lowerSprites, 300);
	player.setAnimation({ lowerAnimation, upperAnimation });
}

void PlayerStateStanding::finish(Player & player)
{
}

PlayerState * PlayerStateStanding::update(Player & player)
{
	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT)) {
		return new PlayerStateWalking(false);
	}
	if (KEY_MANAGER->isStayKeyDown(VK_LEFT)) {
		return new PlayerStateWalking(true);
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LSHIFT)) {
		return new PlayerStateJumping();
	}
	return nullptr;
}


