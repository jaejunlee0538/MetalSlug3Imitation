#pragma once
#include "GameObject.h"
#include "CollisionTriggerBox.h"
#include "SpritesAnimation.h"
#include "Sprite.h"
namespace SGA {
	class TempPlayer :
		public GameObject
	{
	public:
		TempPlayer();
		virtual ~TempPlayer();

		std::string getTag() const {
			return "TempPlayer";
		}

		void update();

		bool isRenderable() const {
			return true;
		}

		void render();
	};
}