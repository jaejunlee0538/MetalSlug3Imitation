#include "GameObjectLoop.h"

namespace SGA {
	namespace GameObjectLoop {
		namespace __private {

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
			for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
				(*it)->beginCollisionCheck();
			}

			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				SGA::GameObject* object1 = *it1;
				if (object1->isActive() == false) {
					continue;
				}
				for (auto it2 = std::next(it1, 1); it2 != gameObjects.end(); ++it2) {
					SGA::GameObject* object2 = *it2;
					if (object2->isActive() == false) {
						continue;
					}
					object1->checkCollisionWith(object2);
				}
			}
			for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
				(*it)->endCollisionCheck();
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

		void gravityLoop(std::vector<SGA::GameObject*>& gameObjects, POINTFLOAT gravity, float dt)
		{
			GameObject* object;
			POINTFLOAT tmp;
			for (auto it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1) {
				object = *it1;
				if (object->isActive() && object->isKinematic()==false &&object->isGravityEnabled()) {
					POINTFLOAT vel = object->getGravityVelocity();
					vel.x += gravity.x * dt;
					vel.y += gravity.y * dt;
					object->setGravityVelocity(vel);

					object->movePosition(vel.x*dt, vel.y*dt);
					//object->movePosition(velocity.x*dt, velocity.y*dt);
					//TODO : velocity*dt로 프레임당 이동을 계산하면 소수점 반올림때문에 플레이어가 위아래로 진동한다.
				}
			}
		}
	}
}