#pragma once
#include "GameObject.h"
#include <vector>
#include <Windows.h>
namespace SGA {
	namespace GameObjectLoop {
		namespace __private {
			void checkCollisionComponent(SGA::CollisionComponent* collision1, SGA::CollisionComponent* collision2);
			void collisionCheckRecursion(SGA::GameObject* object1, SGA::GameObject* object2);
			void renderRecursive(SGA::GameObject* object);
			void updateRecursive(SGA::GameObject* object);
		}

		//TODO : 템플릿화
		//TODO : 모든 자식 Object들끼리도 충돌체크해야하는데 어떻게 for문이랑 재귀를 써야할지 모르겠음.
		//template <typename std::vector>
		void collisionCheckLoop(std::vector<SGA::GameObject*>& gameObjects);

		//template <typename std::vector>
		void renderLoop(std::vector<SGA::GameObject*>& gameObjects);

		//template <typename std::vector>
		void updateLoop(std::vector<SGA::GameObject*>& gameObjects);

		void gravityLoop(std::vector<SGA::GameObject*>& gameObjects, POINTFLOAT velocity, float dt);
	}
}

