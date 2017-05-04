#pragma once
#include <Windows.h>
#include "Camera.h"
namespace SGA {
	class GameLevel
	{
	public:
		GameLevel();
		virtual ~GameLevel();
		virtual void update();
		virtual void render(HDC hdc);
	private:
		Camera _camera;
	};
}