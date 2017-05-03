#include "PlayerStateWalking.h"
#include "Player.h"
#include "Stdafx.h"
#include <SpritesAnimation.h>
#include "PlayerStateStanding.h"
namespace SGA {
	PlayerStateWalking::PlayerStateWalking(bool isLeft)
		:_isLeft(isLeft)
	{
		if (_isLeft) {
			_speedX = -6.0f;
		}
		else {
			_speedX = 6.0f;
		}
	}

	PlayerStateWalking::~PlayerStateWalking()
	{
	}

	void PlayerStateWalking::enter(Player & player)
	{
		std::vector<const SGA::Sprite*> upperSprites, lowerSprites;

		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_0"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_1"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_2"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_3"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_4"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_5"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_6"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_7"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_8"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_9"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_10"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_11"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_12"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_13"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_14"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_15"));
		upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperWalking_16"));

		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_0"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_1"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_2"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_3"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_4"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_5"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_6"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_7"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_8"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_9"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_10"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_11"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_12"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_13"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_14"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_15"));
		lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerWalking_16"));

		SGA::SpritesAnimation * upperAnimation = new SGA::SpritesAnimation(upperSprites, 50);
		SGA::SpritesAnimation * lowerAnimation = new SGA::SpritesAnimation(lowerSprites, 50);
		upperAnimation->enableMirrored(_isLeft);
		lowerAnimation->enableMirrored(_isLeft);
		player.setAnimation({ lowerAnimation, upperAnimation });
	}

	void PlayerStateWalking::finish(Player & player)
	{
	}

	PlayerState * PlayerStateWalking::update(Player & player)
	{
		if (_isLeft == false && KEY_MANAGER->isStayKeyDown(VK_RIGHT) == false) {
			return new PlayerStateStanding();
		}
		if (_isLeft == true && KEY_MANAGER->isStayKeyDown(VK_LEFT) == false) {
			return new PlayerStateStanding();
		}
		player.movePosition(_speedX, 0);
		return nullptr;
	}
}