#include "stdafx.h"
#include "GameWorld.h"
#define MAX_LOADSTRING 100

GameWorld game;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(HWND hWnd, int x, int y, int width, int height);
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpszCmdParam,
	int cmdShow) {
	MSG message;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WIN_NAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	_hInstance = hInstance;
	_hWnd = CreateWindow(
		WIN_NAME,
		WIN_NAME,
		WS_OVERLAPPEDWINDOW,
		WIN_START_X,
		WIN_START_Y,
		WIN_SIZE_X,
		WIN_SIZE_Y,
		NULL,
		NULL,
		hInstance,
		NULL);

	setWindowSize(_hWnd, WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);
	ShowWindow(_hWnd, cmdShow);

	//게임 스터디 초기화
	if (FAILED(game.init())) {
		return 0;
	}

	while (GetMessage(&message, 0, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	game.release();
	UnregisterClass(WIN_NAME, hInstance);
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return game.MainProc(hWnd, message, wParam, lParam);
}

void setWindowSize(HWND hWnd, int x, int y, int width, int height) {
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(hWnd, NULL, x, y, rect.right - rect.left,
		rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
}

