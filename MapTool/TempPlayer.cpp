#include "TempPlayer.h"
#include <KeyManager.h>
#include <Camera.h>
#include <CommonMacroHeader.h>
#include <LayerManager.h>
#include "Stdafx.h"
namespace SGA {
	TempPlayer::TempPlayer()
	{
		disableGravity();
	}

	TempPlayer::~TempPlayer()
	{
	}

	void TempPlayer::update() {
		if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
			movePosition(-10, 0);
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
			movePosition(10, 0);
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
			movePosition(0, -10);
		}

		if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
			movePosition(0, 10);
		}

		POINTFLOAT pos = getPosition();
		RECT clamp = GET_CAMERA()->getScreenRECT();
		if (pos.x < clamp.left) {
			pos.x = clamp.left;
		}
		if (pos.x > clamp.right) {
			pos.x = clamp.right;
		}
		setPosition(pos.x, pos.y);
	}
	void TempPlayer::render()
	{
		Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_GAME_OBJECT);
		layer->drawCircleInWorld(getPosition().x, getPosition().y, 15);
	}
}