#pragma once
#include "SingletonBase.h"
#include <Windows.h>
namespace SGA {
	class ClockIface {
	public:
		virtual ~ClockIface(){}
		virtual DWORD getCurrentTimeMillis() const = 0;
		virtual void reset() = 0;
	};

	class GameWorldClock : public ClockIface, public SingletonBase<GameWorldClock>
	{
	public:
		GameWorldClock() {
			reset();
		}

		DWORD getCurrentTimeMillis() const {
			return _currentClock;
		}

		void updateClock(DWORD dt) {
			_currentClock += dt;
		}

		void reset() {
			_currentClock = 0;
		}
	private:
		DWORD _currentClock;
	};

	class RealTimeClock : public ClockIface,public SingletonBase<RealTimeClock>
	{
	public:
		RealTimeClock() {
			reset();
		}

		DWORD getCurrentTimeMillis() const {
			return _currentClock;
		}

		void updateClock() {
			_currentClock = GetTickCount() - _t0;
		}

		void reset() {
			_t0 = GetTickCount();
			_currentClock = 0;
		}
	private:
		DWORD _currentClock;
		DWORD _t0;
	};

#define GET_GAME_WORLD_CLOCK()	SGA::GameWorldClock::getSingleton()
#define GET_REALTIME_CLOCK()	SGA::RealTimeClock::getSingleton()
}