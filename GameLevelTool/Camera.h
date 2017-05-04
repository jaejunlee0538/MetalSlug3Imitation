#pragma once
#include <Windows.h>
namespace SGA {
	class GameObject;
	class CameraTargetConstraint;
	class Camera
	{
	public:
		Camera(int width, int height);

		virtual ~Camera();

		void update();

		/*
		카메라의 동작을 결정한다.
		*/
		//void setTargetConstraint(CameraTargetConstraint* targetConstraint);

		/*
		카메라가 따라갈 target오브젝트를 설정한다.
		*/
		inline void setTarget(GameObject* target) {
			_targetObject = target;
		}

		inline void setPosition(float x, float y) {
			_position.x = x;
			_position.y = y;
		}

		/*
		게임 레벨 내에서의 현재 카메라 화면의 좌표에 해당하는 RECT를 반환한다.
		*/
		RECT getScreenRECT() const;

		/*
		target을 따라갈 때 부드러운 카메라 이동을 위한 SprintDamper 시스템 매개변수를 설정한다.
		*/
		//void setSpringDamper(float K, float D);

		/*
		true를 설정하면 target을 따라 뒤로 이동한다.
		false를 설정하면 카메라는 왔던 길을 되돌아가지 않는다.
		*/
		//void enableBackstep(bool enable);
	protected:
		GameObject* _targetObject;
		POINTFLOAT _position;//카메라 중심 위치
		int _width, _height;
	};
}