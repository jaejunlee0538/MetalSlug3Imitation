#include "Stdafx.h"
#include "GameNode.h"
#include <RandomFunction.h>

GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::init()
{
	SetTimer(_hWnd, 1, UPDATE_DELTA_TIME, 0);

	return S_OK;
}

void GameNode::release(void)
{
	KillTimer(_hWnd, 1);
}

void GameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;
	}
	case WM_TIMER:
	{
		this->update();
	}
	break;
	case WM_CREATE:
	{
		GET_RANDOM_FUNCTION();//seed value
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		_backBuffer.init(hWnd, clientRect.right, clientRect.bottom);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		hdc = _backBuffer.getBufferDC();
		this->render(hdc);
		_backBuffer.drawBuffer();
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{
		int w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		_backBuffer.resize(w, h);
		const int offset = 0;
		_screenRect.left = 0 + offset;
		_screenRect.right = w- offset;
		_screenRect.top = 0+ offset;
		_screenRect.bottom = h- offset;
		_screenCenter.x = w / 2;
		_screenCenter.y = h / 2;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		GET_RANDOM_FUNCTION()->releaseSingleton();
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
