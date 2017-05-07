#pragma once
#include "GameObject.h"
#include "SpriteIface.h"
#include "SpritesAnimation.h"
#include "Layer.h"
namespace SGA {
	class SpriteObject :
		public GameObject
	{
	public:
		SpriteObject(std::string spriteName, bool animation, int posX, int posY, int renderLayer);
		virtual ~SpriteObject();

		void update();
		bool isRenderable() const {
			return true;
		}
		void render();
	private:
		const Sprite* _sprite;
		SpritesAnimation* _anim;
		Layer* _layer;
	};
}
