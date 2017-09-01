#include "GunPistol.h"
#include "Camera.h"
#include "Global.h"
namespace SGA {
	GunPistol::GunPistol()
	{
		for (int i = 0; i < BULLET_MAX; ++i) {
			addChild(&_bullet[i]);
		}
	}

	GunPistol::~GunPistol()
	{
	}

	void GunPistol::update()
	{
		POINTFLOAT pos;
		RECT rect = GET_CAMERA()->getScreenRECT();
		rect.left -= 30;
		rect.right += 30;
		rect.top -= 30;
		rect.bottom += 30;

		for (int i = 0; i < BULLET_MAX; ++i) {
			if (_bullet[i].isFired()) {
				pos = _bullet[i].getPosition();
				if (pos.x < rect.left || pos.x>rect.right || pos.y<rect.top || pos.y>rect.bottom) {
					_bullet[i].setInactive();
					//OutputDebugString("Bullet Out of Screen\n");
					LogDebugMessage("Bullet out of screen\n");
				}
			}
		}
	}

	void GunPistol::fire(float posX, float posY, int xDir, int yDir)
	{
		float speedX = xDir*400.0f, speedY = yDir*400.0f;
		for (int i = 0; i < BULLET_MAX; ++i) {
			if (_bullet[i].isFired() == false) {
				_bullet[i].setPosition(posX, posY);
				_bullet[i].setVelocity(speedX, speedY);
				_bullet[i].fire();
				break;
			}
		}
	}
}