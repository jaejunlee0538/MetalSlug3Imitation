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
		ī�޶��� ������ �����Ѵ�.
		*/
		//void setTargetConstraint(CameraTargetConstraint* targetConstraint);

		/*
		ī�޶� ���� target������Ʈ�� �����Ѵ�.
		*/
		inline void setTarget(GameObject* target) {
			_targetObject = target;
		}

		inline void setPosition(float x, float y) {
			_position.x = x;
			_position.y = y;
		}

		/*
		���� ���� �������� ���� ī�޶� ȭ���� ��ǥ�� �ش��ϴ� RECT�� ��ȯ�Ѵ�.
		*/
		RECT getScreenRECT() const;

		/*
		target�� ���� �� �ε巯�� ī�޶� �̵��� ���� SprintDamper �ý��� �Ű������� �����Ѵ�.
		*/
		//void setSpringDamper(float K, float D);

		/*
		true�� �����ϸ� target�� ���� �ڷ� �̵��Ѵ�.
		false�� �����ϸ� ī�޶�� �Դ� ���� �ǵ��ư��� �ʴ´�.
		*/
		//void enableBackstep(bool enable);
	protected:
		GameObject* _targetObject;
		POINTFLOAT _position;//ī�޶� �߽� ��ġ
		int _width, _height;
	};
}