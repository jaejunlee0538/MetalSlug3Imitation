#include "GameObjectLoop.h"

namespace SGA {
	namespace GameObjectLoop {
		namespace __private {
			void resolveCollision(SGA::CollisionComponent* collision1, SGA::CollisionComponent* collision2) {
				uint8_t test = collision1->getOwner().isKinematic() ? 0x01 : 0x00;
				test |= collision2->getOwner().isKinematic() ? 0x02 : 0x00;
				switch (test) {
				case 0x00:
				{
					//둘다 일반 Collider
					//collision1->resolveCollisionWith(collision2);
					//TODO : 이럴 때는 어떤 애를 움직여야지?
				}
					break;
				case 0x01:
				{
					//1번이 Kinematic
					collision1->resolveCollisionWith(collision2);
				}
					break;
				case 0x02:
				{
					//2번이 Kinematic
					collision2->resolveCollisionWith(collision1);
				}
					break;
				case 0x03:
				{
					//둘다 Kinamatic
					//아무일도 하지 않음
				}
					break;
				}
			}

			void checkCollisionComponent(SGA::CollisionComponent* collision1, SGA::CollisionComponent* collision2) {
				if (collision1->isCollidableWith(collision2)) {
					if (collision1->isCollideWith(collision2)) {
						collision1->handleCollision(collision2);
						collision2->handleCollision(collision1);
						resolveCollision(collision1, collision2);
					}
					else {
						collision1->handleNoneCollision(collision2);
						collision2->handleNoneCollision(collision1);
					}
				}
			}

			void collisionCheckRecursion(SGA::GameObject* object1, SGA::GameObject* object2) {
				if ((object1->isActive() && object1->isCollidable()) == false) {
					return;
				}
				if ((object2->isActive() && object2->isCollidable()) == false) {
					return;
				}
				checkCollisionComponent(object1->getCollisionComponent(), object2->getCollisionComponent());
				for (auto child = object1->beginChilds(); child != object1->endChilds(); ++child) {
					collisionCheckRecursion(*child, object2);
				}
				for (auto child = object2->beginChilds(); child != object2->endChilds(); ++child) {
					collisionCheckRecursion(object1, *child);
				}
			}

			void renderRecursive(SGA::GameObject* object) {
				if (object->isActive() == false) {
					return;
				}
				if (object->isRenderable()) {
					object->render();
				}
				for (auto child = object->beginChilds(); child != object->endChilds(); ++child) {
					renderRecursive(*child);
				}
			}

			void updateRecursive(SGA::GameObject* object) {
				if (object->isActive() == false) {
					return;
				}
				object->update();
				for (auto child = object->beginChilds(); child != object->endChilds(); ++child) {
					updateRecursive(*child);
				}
			}
		}

		//template <typename std::vector>
		void collisionCheckLoop(std::vector<SGA::GameObject*>& gameObjects) {
			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				SGA::GameObject* object1 = *it1;
				if ((object1->isActive() && object1->isCollidable()) == false) {
					continue;
				}
				for (auto it2 = std::next(it1, 1); it2 != gameObjects.end(); ++it2) {
					SGA::GameObject* object2 = *it2;
					if ((object2->isActive() && object2->isCollidable()) == false) {
						continue;
					}
					__private::collisionCheckRecursion(object1, object2);
				}
			}
		}

		//template <typename std::vector>
		void renderLoop(std::vector<SGA::GameObject*>& gameObjects) {
			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				__private::renderRecursive(*it1);
			}
		}

		//template <typename std::vector>
		void updateLoop(std::vector<SGA::GameObject*>& gameObjects) {
			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				__private::updateRecursive(*it1);
			}
		}

		void gravityLoop(std::vector<SGA::GameObject*>& gameObjects, POINTFLOAT velocity, float dt)
		{
			GameObject* object;
			POINTFLOAT tmp;
			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				object = *it1;
				if (object->isActive() && object->isKinematic()==false &&object->isGravityEnabled()) {
					tmp = object->getPosition();
					tmp.x += velocity.x * dt;
					tmp.y += velocity.y * dt;
					object->setPosition(tmp.x, tmp.y);
				}
			}
		}
	}
}