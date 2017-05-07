#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "CollisionComponent.h"
namespace SGA {
	class CollisionTriggerBox : public GameObject
	{
	public:
		CollisionTriggerBox(int posX, int posY, int width, int height, std::string tag);
		virtual ~CollisionTriggerBox();

		std::string getTag() const {
			return _tag;
		}

		//targetTags ��Ͽ� �ִ� ������Ʈ�� �浹���̸� true�� ��ȯ�Ѵ�.
		inline bool isCollisionTriggered() const
		{
			return _colliding;
		}

		virtual bool isCollidable() const {
			return true;
		}

		//targetTags ���� �±׸� ������ ������Ʈ�� ���ؼ��� Ʈ���Ű� �����Ѵ�.
		//targetTags�� �� ����� �����ϸ� ��� ������Ʈ�� ���Ͽ� Ʈ���Ű� �����Ѵ�.
		inline void setCollisionTarget(const std::vector<std::string>& targetTags)
		{
			_targetTags = targetTags;
		}

		void resizeTriggerBox(int w, int h);

		bool isRenderable() const;

		void render();

		void update();

		void onTrigerringEnter(GameObject& other);
		void onTrigerring(GameObject& other);

		void onTrigerringExit(GameObject& other);
	protected:
		std::string _tag;
		std::vector<std::string> _targetTags;
		bool _colliding;
	};
}