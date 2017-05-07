#include "FrontSprite.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "LayerManager.h"
namespace SGA {

	SpriteObject::SpriteObject(std::string spriteName, bool animation, int posX, int posY, int renderLayer)
	{
		setPosition(posX, posY);
		if (animation) {
			_sprite = NULL;
			_anim = GET_ANIMATION_MANAGER()->findAnimation(spriteName);
		}
		else {
			_sprite = GET_SPRITE_MANAGER()->findSprite(spriteName);
			_anim = NULL;
		}
		_layer = GET_LAYER_MANAGER()->findLayer(GET_LAYER_MANAGER()->getLayerIndexFrom(renderLayer));
	}

	SpriteObject::~SpriteObject()
	{
	}

	void SpriteObject::update() {
		if (_anim) {
			_anim->update();
		}
	}

	void SpriteObject::render()
	{
		if (_anim) {
			_layer->renderInWrold(_anim, getPosition().x, getPosition().y);
		}
		else if(_sprite) {
			_layer->renderInWrold(_sprite, getPosition().x, getPosition().y);
		}
	}
}