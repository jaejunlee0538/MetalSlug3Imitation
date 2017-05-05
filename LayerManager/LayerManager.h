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
		width X heightũ���� ���̾� nLayer���� �����.
		*/
		void init(int width, int height);

		/*
		���� �Ʒ� ���̾���� ������� ȭ�鿡 �׸���.
		*/
		void render(HDC hdc);

		void clearAllLayers();

		/*
		���̾ ��� �����Ѵ�.
		*/
		void release();

		/*
		���� ���̾� ������ ��ȯ�Ѵ�.
		*/
		int getNLayer() const;

		/*
		layerIdx��° ���̾��� �����͸� ��ȯ�Ѵ�.
		*/
		Layer* findLayer(LayersIndex layerName);

		/*
		���̾ �ʱ�ȭ �Ǿ����� true�� ��ȯ�Ѵ�.
		*/
		bool isInitialized()const;
	private:
		Layer* _layer[NUMBER_OF_LAYERS];
	};
#define GET_LAYER_MANAGER() SGA::LayerManager::getSingleton()
}