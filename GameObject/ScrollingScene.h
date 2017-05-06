#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Sprite.h"
#include "Layer.h"
namespace SGA {
	class ScrollingScene :
		public GameObject
	{
	public:
		ScrollingScene(const std::vector<const Sprite*>& sprites, Layer* layer, float sx, float sy);

		virtual ~ScrollingScene();

		std::string getTag() const {
			return "ScrollingScene";
		}

		bool isRenderable() const {
			return true;
		}

		void setCameraInitPos(float posX, float posY) {
			_initCamPos.x = posX;
			_initCamPos.y = posY;
		}

		void render();

		void update();

		void setCamera(Camera * camera);
	private:
		Camera* _camera;
		std::vector<const Sprite*> _scenes;
		int _renderIdx[2];
		int _W, _H;
		POINTFLOAT _actualCamPos;
		POINTFLOAT _virtualCamPos;
		POINTFLOAT _initCamPos;
		POINTFLOAT _scale;
		Layer* _layer;
	};
}