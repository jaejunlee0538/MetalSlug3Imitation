#pragma once
#include <Windows.h>
namespace SGA {
	class SpriteIface {
	public:
		virtual ~SpriteIface(){}
		virtual void render(HDC hdc, int drawPosX, int drawPosY) const= 0;
	};
}