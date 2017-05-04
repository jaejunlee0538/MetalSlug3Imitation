#pragma once
#include <Windows.h>
#include "GameNode.h"
#include <vector>
namespace SGA {
	class Sprite;
	class SpritesAnimation;
}
class GameWorld : public GameNode
{
	struct tagAnimation {
		SGA::SpritesAnimation* animation;
		POINT drawPos;
	};
public:
	GameWorld();

	~GameWorld();

	virtual HRESULT init();

	virtual void release(void);

	virtual void update(float dt);

	virtual void render(HDC hdc);
private:
	//std::vector<const SGA::Sprite*> _animation;
	std::vector<tagAnimation> _animation;
};

