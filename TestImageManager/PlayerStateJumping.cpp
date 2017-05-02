#include "PlayerStateJumping.h"
#include "Player.h"
#include "Stdafx.h"
#include "Sprite.h"
#include "SpritesAnimation.h"
#include "PlayerStateStanding.h"

PlayerStateJumping::PlayerStateJumping()
{
	_speed = -10;
	_gravity = 1;
}


PlayerStateJumping::~PlayerStateJumping()
{
}

void PlayerStateJumping::enter(Player & player)
{
	std::vector<const SGA::Sprite*> upperSprites, lowerSprites;

	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_0"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_1"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_2"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_3"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_4"));
	upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_5"));

	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_0"));
	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_1"));
	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_2"));
	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_3"));
	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_4"));
	lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_5"));

	SpritesAnimation * upperAnimation = new SpritesAnimation(upperSprites, 200, false);
	SpritesAnimation * lowerAnimation = new SpritesAnimation(lowerSprites, 200, false);
	player.setAnimation({ lowerAnimation, upperAnimation });
}

void PlayerStateJumping::finish(Player & player)
{
}

PlayerState * PlayerStateJumping::update(Player & player)
{
	//�ִϸ��̼� ��� �� ������ ��������Ʈ���� ���/�÷��̾� ���� ���� ������ ��
	if (!KEY_MANAGER->isStayKeyDown(VK_LSHIFT)) {
		return new PlayerStateStanding();
	}
	_speed += _gravity;
	player.movePosition(0, _speed);
	return nullptr;
}
