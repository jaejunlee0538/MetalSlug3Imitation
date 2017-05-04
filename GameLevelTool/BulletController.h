#pragma once
namespace SGA {
	class Bullet;
	class GameWorldClock;
	class BulletCtrlIface {
	public:
		virtual ~BulletCtrlIface(){}
		virtual void update(Bullet* bullet) = 0;
		virtual BulletCtrlIface* clone() const= 0;
	};

	class BulletCtrlStraight : public BulletCtrlIface{
	public:
		BulletCtrlStraight(float vx, float vy);
		void update(Bullet* bullet);
		BulletCtrlIface* clone() const {
			return new BulletCtrlStraight(_vx, _vy);
		}
	private:
		float _vx, _vy;
		DWORD _lastTime;
	};

}