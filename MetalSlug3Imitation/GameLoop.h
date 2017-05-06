#pragma once
#include <Windows.h>
#include "GameNode.h"
#include <vector>
#include "Player.h"
#include <GameObject.h>

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
	std::vector<SGA::GameObject*> _gameObjects;
	SGA::Player* _player;
};
