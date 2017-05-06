#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "CollisionComponent.h"
namespace SGA {
	class CollisionTriggerBox : public GameObject
	{
	public:
		CollisionTriggerBox(int posX, int posY, int width, int height);
		virtual ~CollisionTriggerBox();

		std::string getTag() const {
			return "CollTriggerBox";
		}

		//targetTags 목록에 있는 오브젝트와 충돌중이면 true를 반환한다.
		inline bool isCollisionTriggered() const
		{
			return _colliding;
		}

		//targetTags 내의 태그를 가지는 오브젝트에 대해서만 트리거가 동작한다.
		//targetTags로 빈 목록을 설정하면 모든 오브젝트에 대하여 트리거가 동작한다.
		inline void setCollisionTarget(const std::vector<std::string>& targetTags)
		{
			_targetTags = targetTags;
		}

		bool isRenderable() const {
			return false;
		}

		void onTrigerring(GameObject& other);

		void onTrigerringExit(GameObject& other);
	protected:
		std::vector<std::string> _targetTags;
		bool _colliding;
	};
}