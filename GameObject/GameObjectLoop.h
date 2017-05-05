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

		//TODO : ���ø�ȭ
		//TODO : ��� �ڽ� Object�鳢���� �浹üũ�ؾ��ϴµ� ��� for���̶� ��͸� ������� �𸣰���.
		//template <typename std::vector>
		void collisionCheckLoop(std::vector<SGA::GameObject*>& gameObjects);

		//template <typename std::vector>
		void renderLoop(std::vector<SGA::GameObject*>& gameObjects);

		//template <typename std::vector>
		void updateLoop(std::vector<SGA::GameObject*>& gameObjects);

		void gravityLoop(std::vector<SGA::GameObject*>& gameObjects, POINTFLOAT velocity, float dt);
	}
}

