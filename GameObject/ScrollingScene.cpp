#include "ScrollingScene.h"
#include <assert.h>
#include "LayerManager.h"
namespace SGA{
	ScrollingScene::ScrollingScene(const std::vector<const Sprite*>& sprites, Layer* layer, float sx, float sy)
		:_layer(layer), _scenes(sprites)
	{
		_scale.x = sx;
		_scale.y = sy;
		_W = _scenes[0]->getWidth();
		_H = _scenes[0]->getHeight();
		_camera = GET_CAMERA();
		disableGravity();
		enableKinematic();
		setActive();
	}

	ScrollingScene::~ScrollingScene()
	{
	}

	void ScrollingScene::render()
	{
		_actualCamPos = _camera->getPosition();

		_virtualCamPos.x = _initCamPos.x + (_actualCamPos.x - _initCamPos.x)*_scale.x;
		_virtualCamPos.y = _initCamPos.y + (_actualCamPos.y - _initCamPos.y)*_scale.y;

		_renderIdx[0] = (_virtualCamPos.x - _camera->getCameraWidth() / 2) / _W;
		_renderIdx[1] = (_virtualCamPos.x + _camera->getCameraWidth() / 2) / _W;
		assert(_renderIdx[0] >= 0);
		assert(_renderIdx[1] < _scenes.size());

		for (int i = _renderIdx[0]; i <= _renderIdx[1]; ++i) {
			_layer->renderInWrold(_scenes[i],
				_actualCamPos.x + _W / 2 + i*_W - _virtualCamPos.x,
				_actualCamPos.y + _H / 2 - _virtualCamPos.y);
		}
	}

	void ScrollingScene::update()
	{

	}

	void ScrollingScene::setCamera(Camera * camera)
	{
		_camera = camera;
	}
}