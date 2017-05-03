#pragma once
#include <Windows.h>
#include <vector>
namespace SGA {
	class SpritesAnimation;
	class PlayerState;
	class Player
	{
	public:
		Player();
		~Player();

		void update();

		void render(HDC hdc);

		void setAnimation(const std::vector<SpritesAnimation*>& animations) {
			_animations = animations;
		}

		void setPosition(float x, float y) {
			_x = x;
			_y = y;
		}

		void movePosition(float dx, float dy) {
			setPosition(_x + dx, _y + dy);
		}

		POINTFLOAT getPosition() const {
			return{ _x, _y };
		}
	private:
		float _x, _y;
		PlayerState* _state;
		std::vector<SpritesAnimation*> _animations;
	};

}