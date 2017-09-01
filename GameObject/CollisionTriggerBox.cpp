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
