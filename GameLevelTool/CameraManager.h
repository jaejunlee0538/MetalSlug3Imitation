#pragma once
#include "Camera.h"
#include <SingletonBase.h>
namespace SGA {
	class CameraManager : public SingletonBase<CameraManager>
	{
	public:
		CameraManager();
		virtual ~CameraManager();
		void init(int width, int height);
		void release();
		Camera* getCamera();
	private:
		Camera* _camera;
	};

#define GET_CAMERA_MANAGER() SGA::CameraManager::getSingleton()
}