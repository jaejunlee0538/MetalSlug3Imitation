#include "CollisionTriggerBox.h"
#include "CollisionComponentRectangle.h"
#include "CommonMacroHeader.h"
#include <algorithm>
#include "CollisionConfig.h"
#include "Global.h"
#include "LayerManager.h"
#include "KeyManager.h"
namespace SGA {

	CollisionTriggerBox::CollisionTriggerBox(int posX, int posY, int width, int height, std::string tag)
	:_tag(tag){
		setPosition(posX, posY);
		resizeTriggerBox(width, height);
		disableGravity();
		enableKinematic();
		_colliding = false;
	}

	CollisionTriggerBox::~CollisionTriggerBox() {

	}

	void CollisionTriggerBox::onCollidingEnter(GameObject & other)
	{
		//LogDebugMessage("TriggeringEnter - %s\n", other.getTag().c_str());
	}

	void CollisionTriggerBox::onColliding(GameObject & other)
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
		//_colliding = false;
		LogDebugMessage("TriggeringExit - %s\n", other.getTag().c_str());

	}

	void CollisionTriggerBox::setCollisionLayer(CollisionLayers layer)
	{
		getCollisionComponent()->setCollisionLayer(layer);
	}

	void CollisionTriggerBox::resizeTriggerBox(int w, int h)
	{
		CollisionComponentRectangle * rectCollision =
			new CollisionComponentRectangle(*this,
				SGA::makeRectCenter<RECT, int>(0, 0, w, h),
				true, COLLISION_LAYER_TRIGGER_BOX);
		CollisionComponent* oldCollision= setCollisionComponent(rectCollision);
		
		if (oldCollision) {
			delete oldCollision;
		}
	}

	bool CollisionTriggerBox::isRenderable() const {
#if DEBUG_ENABLE_DRAW_COLLISION_TRIGGER_BOX
		return GET_KEY_MANAGER()->isToggleKey('2');
#else
		return false;
#endif
	}

	void CollisionTriggerBox::render() {
#if DEBUG_ENABLE_DRAW_COLLISION_TRIGGER_BOX
		Layer* layer = GET_LAYER_MANAGER()->findLayer(LayerManager::LAYER_INDEX_SCENE_FOREGROUND);
		CollisionComponentRectangle* collider = dynamic_cast<CollisionComponentRectangle*>(getCollisionComponent());
		layer->drawRectangleInWorld(collider->getCollisionRECT());
#endif
	}

	void CollisionTriggerBox::update()
	{
		_colliding = false;
	}

}
