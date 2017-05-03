#include "PlayerStateJumping.h"
#include "Player.h"
#include "Stdafx.h"
#include <Sprite.h>
#include <SpritesAnimation.h>
#include "PlayerStateStanding.h"
#include <AnimationManager.h>
namespace SGA {
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

		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_0"));
		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_1"));
		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_2"));
		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_3"));
		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_4"));
		//upperSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/UpperJumpingStayStill_5"));

		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_0"));
		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_1"));
		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_2"));
		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_3"));
		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_4"));
		//lowerSprites.push_back(SPRITE_MANAGER->findSprite("CharacterTarmaWithPistol/LowerJumpingStayStill_5"));

		SGA::SpritesAnimation * upperAnimation = SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_UpperRight");
		SGA::SpritesAnimation * lowerAnimation = SGA::AnimationManager::getSingleton()->findAnimation("JumpingStayStill_LowerRight");
		player.setAnimation({ lowerAnimation, upperAnimation });
	}

	void PlayerStateJumping::finish(Player & player)
	{
	}

	PlayerState * PlayerStateJumping::update(Player & player)
	{
		//애니메이션 재생 후 마지막 스프라이트에서 대기/플레이어 발이 땅에 닿으면 끝
		if (!KEY_MANAGER->isStayKeyDown(VK_LSHIFT)) {
			return new PlayerStateStanding();
		}
		_speed += _gravity;
		player.movePosition(0, _speed);
		return nullptr;
	}
}