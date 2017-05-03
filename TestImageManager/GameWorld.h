#pragma once
#include <Windows.h>
#include "GameNode.h"
#include <vector>
#include "Player.h"
class GameWorld : public GameNode
{
public:
	GameWorld();

	~GameWorld();

	virtual HRESULT init();

	void processKeyInput();

	virtual void release(void);

	virtual void update(float dt);

	virtual void render(HDC hdc);
private:
	SGA::Player *_player;
};

