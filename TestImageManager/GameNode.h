#pragma once
#pragma once
#include <Windows.h>
#include "DoubleBuffering.h"

class GameNode
{
public:
	GameNode();
	virtual ~GameNode();

	/*
	WM_CREATE
	*/
	virtual HRESULT init();

	/*
	WM_DESTROY
	*/
	virtual void release(void);
	
	/*
	WM_TIMER
	*/
	virtual void update(float dt);
	
	/*
	WM_PAINT
	*/
	virtual void render(HDC hdc);

	inline POINT getMousePosition() const {
		return _ptMouse;
	}

	inline void clearScreen(COLORREF color) {
		_backBuffer.clearBuffer(color);
	}

	const RECT& getScreenSize() const {
		return _screenRect;
	}

	const POINT& getScreenCenter() const {
		return _screenCenter;
	}
	/*
	*/
	LRESULT MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	SGA::DoubleBuffering _backBuffer;
	POINT _ptMouse;
	RECT _screenRect;
	POINT _screenCenter;
};

