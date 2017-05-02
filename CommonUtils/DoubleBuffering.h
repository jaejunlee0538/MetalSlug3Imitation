#pragma once
#include <Windows.h>
#include <assert.h>
namespace SGA {
	class DoubleBuffering
	{
	public:
		DoubleBuffering() {
			_hdc = NULL;
		}
		~DoubleBuffering() {
			destroy();
		}

		void init(HWND hWnd, int width, int height) {
			destroy();
			_hWnd = hWnd;
			_hdc = GetDC(hWnd);
			_memDC = CreateCompatibleDC(_hdc);
			resize(width, height);
		}

		bool isInitialized() const {
			return _hdc != NULL;
		}

		void resize(int width, int height) {
			assert(isInitialized());
			HBITMAP bitmapNew = CreateCompatibleBitmap(_hdc, width, height);
			SelectObject(_memDC, bitmapNew);
			DeleteObject(_bitmap);
			_bitmap = bitmapNew;
			_w = width;
			_h = height;
		}

		HDC getBufferDC() const {
			assert(isInitialized());
			return _memDC;
		}

		void clearBuffer(COLORREF color = RGB(255, 255, 255)) const {
			assert(isInitialized());
			//BitBlt(_memDC, 0, 0, _w, _h, 0, 0, 0, WHITENESS);

			SelectObject(_memDC, GetStockObject(DC_PEN));
			COLORREF colorOldPen = SetDCPenColor(_memDC, color);
			SelectObject(_memDC, GetStockObject(DC_BRUSH));
			COLORREF colorOld = SetDCBrushColor(_memDC, color);
			Rectangle(_memDC, 0, 0, _w, _h);
			SetDCBrushColor(_memDC, colorOld);
			SetDCPenColor(_memDC, colorOldPen);
		}

		void drawBuffer() const {
			assert(isInitialized());
			BitBlt(_hdc, 0, 0, _w, _h, _memDC, 0, 0, SRCCOPY);
		}

		void destroy() {
			if (_hdc != NULL) {
				ReleaseDC(_hWnd, _hdc);
				_hdc = NULL;
				DeleteObject(_memDC);
				DeleteObject(_bitmap);
			}
		}

		int getWidth() const {
			return _w;
		}

		int getHeight() const {
			return _h;
		}
	private:
		HWND _hWnd;
		int _w, _h;
		HDC _hdc;
		HDC _memDC;
		HBITMAP _bitmap;
	};
}