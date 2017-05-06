#pragma once
#include <GameObject.h>
#include <CollisionComponentRectangle.h>
#include <LayerManager.h>
#include <SpriteManager.h>
#include <KeyManager.h>
namespace SGA {
	class TestBoxObject :
		public GameObject
	{
	public:
		TestBoxObject(RECT rect, POINTFLOAT pos, bool trigger, CollisionLayers collisionLayers, bool controlled,
			std::string sprite1, std::string sprite2) {
			setPosition(pos.x, pos.y);
			_controlled = controlled;
			_collision = new CollisionComponentRectangle(*this, rect, trigger, collisionLayers);
			setCollisionComponent(_collision);
			_spriteIdle = GET_SPRITE_MANAGER()->findSprite(sprite1);
			_spriteActive = GET_SPRITE_MANAGER()->findSprite(sprite2);
			
			_rect = rect;
			setActive();
			_collided = false;
		}

		virtual ~TestBoxObject() {
			delete _collision;
		}

		std::string getTag() const {
			return "MyTestBox";
		}

		void update() {
			if (_controlled) {
				POINTFLOAT pos = getPosition();
				if (GET_KEY_MANAGER()->isStayKeyDown(VK_RIGHT)) {
					pos.x += 4;
				}
				if (GET_KEY_MANAGER()->isStayKeyDown(VK_LEFT)) {
					pos.x -= 4;
				}
				if (GET_KEY_MANAGER()->isStayKeyDown(VK_UP)) {
					pos.y -= 4;
				}
				if (GET_KEY_MANAGER()->isStayKeyDown(VK_DOWN)) {
					pos.y += 4;
				}
				setPosition(pos.x, pos.y);
			}
		}

		void render() {
			Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_GAME_OBJECT);
			if (_collided) {
				layer->renderOnScreen(_spriteActive, getPosition().x, getPosition().y);
			}
			else {
				layer->renderOnScreen(_spriteIdle, getPosition().x, getPosition().y);
			}
		}

		virtual bool isRenderable() const{
			return true;
		}

		virtual void onCollidingEnter(GameObject& other) {
			_collided = true;
		}
		virtual void onColliding(GameObject& other) {
		}
		virtual void onCollidingExit(GameObject& other) {
			_collided = false;
		}
		virtual void onTrigerringEnter(GameObject& other) {
			_collided = true;
		}
		virtual void onTrigerring(GameObject& other) {
		}
		virtual void onTrigerringExit(GameObject& other) {
			_collided = false;
		}
	protected:
		CollisionComponentRectangle *_collision;
		const Sprite* _spriteIdle;
		const Sprite* _spriteActive;
		RECT _rect;
		bool _controlled;
		bool _collided;
	};
}