#pragma once
#include "SingletonBase.h"
#include <Windows.h>
namespace SGA {
	class ClockIface {
	public:
		virtual ~ClockIface(){}
		virtual DWORD getCurrentTimeMillis() const = 0;
		virtual DWORD getDeltaTimeMillis() const = 0;
		virtual void reset() = 0;
	};

	class GameWorldClock : public ClockIface, public SingletonBase<GameWorldClock>
	{
	public:
		GameWorldClock() {
			reset();
		}

		DWORD getCurrentTimeMillis() const {
			return _currentTime;
		}

		DWORD getDeltaTimeMillis() const {
			return _deltaTime;
		}

		void updateClock(DWORD dt) {
			_deltaTime = dt;
			_currentTime += dt;
		}

		void reset() {
			_deltaTime = 0;
			_currentTime = 0;
		}
	private:
		DWORD _deltaTime;
		DWORD _currentTime;
	};

	class RealTimeClock : public ClockIface,public SingletonBase<RealTimeClock>
	{
	public:
		RealTimeClock() {
			reset();
		}

		DWORD getCurrentTimeMillis() const {
			return _currentTime;
		}

		DWORD getDeltaTimeMillis() const {
			return _deltaTime;
		}

		void updateClock() {
			_deltaTime = (GetTickCount() - _t0) - _currentTime;
			_currentTime += _deltaTime;
		}

		void reset() {
			_t0 = GetTickCount();
			_currentTime = 0;
			_deltaTime = 0;
		}
	private:
		DWORD _deltaTime;
		DWORD _currentTime;
		DWORD _t0;
	};

#define GET_GAME_WORLD_CLOCK()	SGA::GameWorldClock::getSingleton()
#define GET_REALTIME_CLOCK()	SGA::RealTimeClock::getSingleton()
}