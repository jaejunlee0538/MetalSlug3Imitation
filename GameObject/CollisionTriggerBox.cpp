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
			//타겟 목록에 없는 물체와 충돌
			return;
		}
		_colliding = true;
	}

	void CollisionTriggerBox::onTrigerringExit(GameObject & other)
	{
		//TODO : 여러 물체와 충돌중일 때 버그 발생할 것으로 예상됨.
		//충돌 개수를 카운트 해야하나?
		//Enter와 Exit가 동일 횟수만큼 호출된다는 보장이 있나?
		_colliding = false;
	}
}
