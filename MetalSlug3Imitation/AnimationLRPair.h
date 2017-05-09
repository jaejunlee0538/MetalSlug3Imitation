#pragma once
#include <string>
#include <SpritesAnimation.h>
namespace SGA {
	class AnimationLRPair {
	public:
		AnimationLRPair();
		~AnimationLRPair();
		void init(std::string animationName);

		SpritesAnimation* get(bool left) {
			if (left)
				return _leftAnimation;
			return _rightAnimation;
		}

		SpritesAnimation* getLeft() {
			return _leftAnimation;
		}
		SpritesAnimation* getRight() {
			return _rightAnimation;
		}
	private:
		SpritesAnimation * _leftAnimation;
		SpritesAnimation * _rightAnimation;

	};
}