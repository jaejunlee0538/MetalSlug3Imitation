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

		//targetTags ��Ͽ� �ִ� ������Ʈ�� �浹���̸� true�� ��ȯ�Ѵ�.
		inline bool isCollisionTriggered() const
		{
			return _colliding;
		}

		//targetTags ���� �±׸� ������ ������Ʈ�� ���ؼ��� Ʈ���Ű� �����Ѵ�.
		//targetTags�� �� ����� �����ϸ� ��� ������Ʈ�� ���Ͽ� Ʈ���Ű� �����Ѵ�.
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