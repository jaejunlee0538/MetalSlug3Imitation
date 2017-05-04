#pragma once
#include <Windows.h>
namespace SGA {
	class BitmapImage
	{
		typedef struct tagImageInfo {
			HDC hMemDC;
			HBITMAP hBit;
			HBITMAP hOBit;
			int width;
			int height;

			tagImageInfo() {
				hMemDC = NULL;
				hBit = NULL;
				hOBit = NULL;
				width = 0;
				height = 0;
			}
		} IMAGE_INFO, *LPIMAGE_INFO;
	public:
		BitmapImage();
		virtual ~BitmapImage();

		static void setHWND(HWND hWnd);
		/*
		source의 좌우가 반전된 비트맵을 가진 BitmapImage객체를 생성한다.
		*/
		static BitmapImage* createMirroredImage(BitmapImage& source);

		HRESULT init(int width, int height);
		HRESULT init(const TCHAR* fileName, int width, int height, BOOL tran = FALSE, COLORREF transColor = RGB(0, 0, 0));
		HRESULT init(const TCHAR* fileName, BOOL tran = FALSE, COLORREF transColor = RGB(0, 0, 0));
		void release();

		void render(HDC hdc, int destX, int destY)  const;
		void render(HDC hdc, int destX, int destY, int destWidth, int destHeight) const;
		void render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight) const;
		void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight) const;

		/*
		이미지를 color색으로 칠한다.
		*/
		void clearImage(COLORREF color);

		inline HDC getDC() const{
			return _imageInfo->hMemDC;
		}
		inline BOOL isInitialized() const {
			return _imageInfo != NULL;
		}
		inline void setTransparentColor(COLORREF transparentColor) {
			_transparentColor = transparentColor;
		}
		inline void enableTransparent(BOOL enable) {
			_isTransparentEnabled = enable;
		}
		inline int getWidth() const {
			return _imageInfo->width;
		}
		inline int getHeight() const {
			return _imageInfo->height;
		}
		inline const TCHAR* getFileName() const {
			return _fileName;
		}
		inline COLORREF getKeyColor() const {
			return _transparentColor;
		}
	private:
		//복사 방지
		BitmapImage(const BitmapImage& other){}
		
	private:
		LPIMAGE_INFO _imageInfo;
		BOOL _isTransparentEnabled;
		COLORREF _transparentColor;
		TCHAR* _fileName;
		static HWND _hWnd;
	};
}
