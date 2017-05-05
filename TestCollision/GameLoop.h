#pragma once
#include <Windows.h>
#include "GameNode.h"
#include <vector>
namespace SGA {
	class GameObject;
}
class GameLoop : public GameNode
{
public:
	GameLoop();

	~GameLoop();

	virtual HRESULT init();

	virtual void release(void);

	virtual void update(void);

	virtual void render(HDC hdc);
private:
	void collisionCheck();
private:
	std::vector<SGA::GameObject*> _gameObjects;
};
