#include "GameMission.h"
#include "Stdafx.h"
#include "WorldClock.h"
#include <CameraManager.h>
namespace SGA {
	void GameMission::init(){
		GET_GAME_WORLD_CLOCK()->reset();
		GET_CAMERA_MANAGER()->init(WIN_SIZE_X, WIN_SIZE_Y);
		GET_CAMERA_MANAGER()->getCamera()->setPosition(WIN_SIZE_X/2, WIN_SIZE_Y/2);

	}

	void GameMission::update() {
		GET_GAME_WORLD_CLOCK()->updateClock(UPDATE_DELTA_TIME);
	}

	void GameMission::render()
	{
	}
}