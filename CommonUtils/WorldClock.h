#pragma once
#include "SingletonBase.h"
#include <Windows.h>
namespace SGA {
	class WorldClock : public SingletonBase<WorldClock>
	{
	public:
		WorldClock() {
			_t0 = GetTickCount();
			_currentClock = 0;
		}

		DWORD getCurrentTimeMillis() const {
			return _currentClock;
		}

		float getCurrentTimeSec() const {
			return _currentClock*0.001f;
		}

		void updateClock() {
			_currentClock = GetTickCount() - _t0;
		}
	private:
		DWORD _currentClock;
		DWORD _t0;
	};
}