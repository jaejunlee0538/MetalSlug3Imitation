#pragma once
#include <GameObject.h>
#include <CollisionComponentRectangleRotated.h>
#include <LayerManager.h>
#include <SpriteManager.h>
#include <KeyManager.h>
#include <MathUtils.h>
namespace SGA {
	class TestRotatedBoxObject :
		public GameObject
	{
	public:
		TestRotatedBoxObject(RECT rect, float angle, POINTFLOAT pos, bool trigger, CollisionLayers collisionLayers) {
			setPosition(pos.x, pos.y);
			_collision = new CollisionComponentRectangleRotated(*this, rect, angle, trigger, collisionLayers);
			setCollisionComponent(_collision);

			_rect = rect;
			_angle = angle;

			setActive();
		}

		virtual ~TestRotatedBoxObject() {
			delete _collision;
		}

		std::string getTag() const {
			return "MyTestBox";
		}

		void update() {
	
		}

		void render() {
			Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_GAME_OBJECT);
			POINTFLOAT p[4];
			SGA::getRotatedRECT(_rect, _angle, p);
			POINT p2[4];
			for (int i = 0; i < 4; i++) {
				p2[i].x = p[i].x + getPosition().x;
				p2[i].y = p[i].y + getPosition().y;
			}
			Polygon(layer->getDC(), p2, 4);
			//layer->drawPolygon(p, 4);
			//layer->drawRectangleInWorld(getPosition().x, getPosition().y, 20, 5);
		}

		virtual bool isRenderable() const {
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
		CollisionComponentRectangleRotated *_collision;
		RECT _rect;

		float _angle;
		bool _collided;
	};
}