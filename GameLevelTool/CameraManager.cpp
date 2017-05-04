#include "CameraManager.h"
#include <assert.h>
#include "Camera.h"
namespace SGA {
	CameraManager::CameraManager()
		:_camera(NULL)
	{
	}


	CameraManager::~CameraManager()
	{
		release();
	}

	void CameraManager::init(int width, int height)
	{
		_camera = new Camera(width, height);
	}

	void CameraManager::release()
	{
		if (_camera) {
			delete _camera;
			_camera = NULL;
		}
	}

	Camera * CameraManager::getCamera()
	{
		assert(_camera != NULL);
		return _camera;
	}
}