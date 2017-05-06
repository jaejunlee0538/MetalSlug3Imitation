#pragma once
#include "GameObject.h"
#include "SingletonBase.h"
#include "WorldClock.h"
namespace SGA {
	class Camera :
		public GameObject, public SingletonBase<Camera>
	{
	public:
		Camera();

		virtual ~Camera();

		void update() {
			//movePosition(5, sin(GET_GAME_WORLD_CLOCK()->getCurrentTimeMillis()*0.001));
			if (_target) {
				POINTFLOAT targetPos = _target->getPosition();
				if (targetPos.x < getCameraWidth() / 2) {
					targetPos.x = getCameraWidth() / 2;
				}
				setPosition(targetPos.x, getPosition().y);
			}
		}

		void init(int width, int height, float posX, float posY) {
			setPosition(posX, posY);
			_width = width;
			_height = height;
		}

		void transformWorldToScreen(float& x, float& y) const;

		std::string getTag() const {
			return "Camera";
		}

		void setTarget(GameObject* target) {
			_target = target;
		}

		int getCameraWidth() const {
			return _width;
		}

		int getCameraHeight() const {
			return _height;
		}

		bool isRenderable() const { 
			return false;
		}

		RECT getScreenRECT() const;
	private:
		int _width;
		int _height;
		GameObject* _target;
	};
#define GET_CAMERA() SGA::Camera::getSingleton()
}