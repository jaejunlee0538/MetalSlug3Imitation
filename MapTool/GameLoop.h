#pragma once
#include <Windows.h>
#include "GameNode.h"
#include <vector>
#include "TempPlayer.h"
#include <GameObject.h>
#include <GroundRectangleRotated.h>
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
	void processKeyInput();
private:
	std::vector<SGA::GameObject*> _gameObjects;
	std::list<SGA::GroundRectangleRotated*> _grounds;
	SGA::TempPlayer* _player;
};
