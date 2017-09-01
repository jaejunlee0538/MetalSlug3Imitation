#include "AnimationLRPair.h"
#include "AnimationManager.h"

namespace SGA {
	AnimationLRPair::AnimationLRPair() {
		_leftAnimation = _rightAnimation = NULL;
	}

	AnimationLRPair::~AnimationLRPair()
	{
		if (_leftAnimation) {
			_leftAnimation->clearActive();
		}
		if (_rightAnimation) {
			_rightAnimation->clearActive();
		}
	}

	void AnimationLRPair::init(std::string animationName)
	{
		std::string tmp = animationName + "_Left";
		_leftAnimation = GET_ANIMATION_MANAGER()->findAnimation(tmp);
		tmp = animationName + "_Right";
		_rightAnimation = GET_ANIMATION_MANAGER()->findAnimation(tmp);
	}
}