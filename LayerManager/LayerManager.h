#pragma once
#include <SingletonBase.h>
#include "Layer.h"
#include <vector>
#include <Windows.h>
namespace SGA {
	
	class LayerManager : public SingletonBase<LayerManager>
	{
	public:
		enum LayersIndex {
			LAYER_IDDEX_SCENE_BACKGROUND = 0,
			LAYER_INDEX_SCENE_WORLD,
			LAYER_INDEX_GAME_OBJECT,
			LAYER_INDEX_SCENE_FOREGROUND,
			LAYER_INDEX_GAME_STATE_UI,
			LAYER_INDEX_GAME_MENU,

			NUMBER_OF_LAYERS
		};

		LayerManager();

		virtual ~LayerManager();

		/*
		width X height크기의 레이어 nLayer개를 만든다.
		*/
		void init(int width, int height);

		/*
		가장 아래 레이어부터 순서대로 화면에 그린다.
		*/
		void render(HDC hdc);

		void clearAllLayers();

		/*
		레이어를 모두 삭제한다.
		*/
		void release();

		/*
		현재 레이어 개수를 반환한다.
		*/
		int getNLayer() const;

		/*
		layerIdx번째 레이어의 포인터를 반환한다.
		*/
		Layer* findLayer(LayersIndex layerName);

		/*
		레이어가 초기화 되었으면 true를 반환한다.
		*/
		bool isInitialized()const;
	private:
		Layer* _layer[NUMBER_OF_LAYERS];
	};
#define GET_LAYER_MANAGER() SGA::LayerManager::getSingleton()
}