#include "LayerManager.h"
#include <assert.h>
#include <algorithm>
namespace SGA {
	#define TRANSPARENT_KEY_COLOR	RGB(255,0,255)

	LayerManager::LayerManager()
	{
		for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
			_layer[i] = NULL;
		}
	}


	LayerManager::~LayerManager()
	{
		release();
	}

	void LayerManager::init(int width, int height)
	{
		release();
		for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
			_layer[i] = new Layer(width, height, TRANSPARENT_KEY_COLOR, true);
		}
	}

	void LayerManager::render(HDC hdc)
	{
		assert(isInitialized());
		for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
			_layer[i]->renderThisLayer(hdc);
		}
	}

	void LayerManager::release()
	{
		for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
			if (_layer[i] != NULL) {
				delete _layer[i];
				_layer[i] = NULL;
			}
		}
	}

	int LayerManager::getNLayer() const
	{
		return NUMBER_OF_LAYERS;
	}

	Layer * LayerManager::findLayer(LayersIndex layerName)
	{
		assert(isInitialized());
		assert(layerName >= 0);
		assert(layerName < NUMBER_OF_LAYERS);

		return _layer[layerName];
	}
	
	bool LayerManager::isInitialized() const {
		return _layer[0] != NULL;
	}
}