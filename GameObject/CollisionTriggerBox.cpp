#include "CollisionTriggerBox.h"
#include "CollisionComponentRectangle.h"
#include "CommonMacroHeader.h"
#include <algorithm>
#include "CollisionConfig.h"

namespace SGA {

	CollisionTriggerBox::CollisionTriggerBox(int posX, int posY, int width, int height)
	{
		setPosition(posX, posY);
		CollisionComponentRectangle * rectCollision = 
			new CollisionComponentRectangle(*this,
				SGA::makeRectCenter<RECT,int>(0, 0, width, height),
				true, COLLISION_LAYER_TRIGGER_BOX);
		setCollisionComponent(rectCollision);
		disableGravity();
		enableKinematic();
		_colliding = false;
	}

	CollisionTriggerBox::~CollisionTriggerBox() {

	}

	void CollisionTriggerBox::onTrigerring(GameObject & other)
	{
		if (_targetTags.empty()) {
			_colliding = true;
			return;
		}
		
		if (std::find(_targetTags.begin(), _targetTags.end(), other.getTag()) == _targetTags.end()) {
			//Ÿ�� ��Ͽ� ���� ��ü�� �浹
			return;
		}
		_colliding = true;
	}

	void CollisionTriggerBox::onTrigerringExit(GameObject & other)
	{
		//TODO : ���� ��ü�� �浹���� �� ���� �߻��� ������ �����.
		//�浹 ������ ī��Ʈ �ؾ��ϳ�?
		//Enter�� Exit�� ���� Ƚ����ŭ ȣ��ȴٴ� ������ �ֳ�?
		_colliding = false;
	}
}
