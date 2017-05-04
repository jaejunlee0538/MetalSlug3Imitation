#include "BulletController.h"
#include "Bullet.h"
#include <WorldClock.h>
namespace SGA {

	BulletCtrlStraight::BulletCtrlStraight(float vx, float vy)
		:_vx(vx), _vy(vy)
	{
		_lastTime = GET_GAME_WORLD_CLOCK()->getCurrentTimeMillis();
	}

	void BulletCtrlStraight::update(Bullet * bullet)
	{
		DWORD t = GET_GAME_WORLD_CLOCK()->getCurrentTimeMillis();
		float dt = (t - _lastTime)*0.001f;
		bullet->movePosition(_vx*dt, _vy*dt);
	}
}