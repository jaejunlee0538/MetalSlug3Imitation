#include "BitmapImage.h"
#include <assert.h>
#include <tchar.h>
#include "CommomMacro.h"
namespace SGA {
	HWND BitmapImage::_hWnd = 0;

	BitmapImage::BitmapImage()
		:_imageInfo(NULL),
		_fileName(NULL),
		_isTransparentEnabled(FALSE)
	{
		//비트맵 객체 생성하기 전에 Window Handle을 반드시 세팅할 것
		//BitmapImage::setHWND(hWnd);
		assert(BitmapImage::_hWnd != 0);
	}

	BitmapImage::~BitmapImage()
	{
		//반드시 수동으로 release할것!
		//파괴자에서 하게 할까?
		//assert(_imageInfo == 0);
		release();
	}

	void BitmapImage::setHWND(HWND hWnd)
	{
		BitmapImage::_hWnd = hWnd;
	}

	BitmapImage * BitmapImage::createMirroredImage(BitmapImage & source)
	{
		BitmapImage* mirroredImage = new BitmapImage();
		mirroredImage->init(source.getWidth(), source.getHeight());
		if (mirroredImage->_fileName != NULL) {
			mirroredImage->_fileName = new TCHAR[_tcslen(source._fileName) + 1];
			_tcscpy(mirroredImage->_fileName, source._fileName);
		}
		mirroredImage->_isTransparentEnabled = source._isTransparentEnabled;
		mirroredImage->_transparentColor = source._transparentColor;
		StretchBlt(mirroredImage->_imageInfo->hMemDC,
			mirroredImage->getWidth()-1, 0,
			-mirroredImage->getWidth(), mirroredImage->getHeight(),
			source._imageInfo->hMemDC,
			0, 0,
			mirroredImage->getWidth(), mirroredImage->getHeight(),
			SRCCOPY);
		return mirroredImage;
	}

	HRESULT BitmapImage::init(int width, int height)
	{
		//재할당 방지
		if (_imageInfo != NULL) release();

		//DC 얻어온다
		HDC hdc = GetDC(BitmapImage::_hWnd);

		_imageInfo = new IMAGE_INFO;
		//비트맵 출력을 위해서 메모리 DC를 만들어 준다
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일경로이름
		_fileName = NULL;

		//얻은 DC 해제한다
		ReleaseDC(_hWnd, hdc);

		//투명 컬러 셋팅!
		_transparentColor = FALSE;

		//이미지 초기화에 실패하면..
		if (_imageInfo->hBit == NULL)
		{
			release();
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT BitmapImage::init(const TCHAR * fileName, int width, int height, BOOL tran, COLORREF transColor)
	{
		//경로값이 없으면
		if (fileName == NULL) return E_FAIL;

		//재할당 방지
		if (_fileName != NULL) release();

		HDC hdc = GetDC(BitmapImage::_hWnd);
		_imageInfo = new IMAGE_INFO();
		//비트맵 출력을 위해서 메모리 DC를 만들어 준다.
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일 경로 저장
		int len = _tcslen(fileName);
		_fileName = new TCHAR[len + 1];
		_tcscpy_s(_fileName, len + 1, fileName);

		ReleaseDC(_hWnd, hdc);

		//투명 컬러 세팅
		_isTransparentEnabled = tran;
		_transparentColor = transColor;

		//이미지 초기화에 실패하면
		if (_imageInfo->hBit == NULL) {
			release();
			return E_FAIL;
		}
		return S_OK;
	}

	HRESULT BitmapImage::init(const TCHAR * fileName, BOOL tran, COLORREF transColor)
	{
		//경로값이 없으면
		if (fileName == NULL) return E_FAIL;

		//재할당 방지
		if (_fileName != NULL) release();

		HDC hdc = GetDC(BitmapImage::_hWnd);
		_imageInfo = new IMAGE_INFO();
		//비트맵 출력을 위해서 메모리 DC를 만들어 준다.
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		//실제 이미지 크기로 이미지를 로드한다.
		_imageInfo->hBit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		//읽어들인 이미지 파일의 실제 크기를 알아낸다.
		BITMAP bmp = { 0 };
		GetObject(_imageInfo->hBit, sizeof(bmp), &bmp);
		_imageInfo->width = bmp.bmWidth;
		_imageInfo->height = bmp.bmHeight;

		//파일 경로 저장
		int len = _tcslen(fileName);
		_fileName = new TCHAR[len + 1];
		_tcscpy_s(_fileName, len + 1, fileName);

		ReleaseDC(_hWnd, hdc);

		//투명 컬러 세팅
		_isTransparentEnabled = tran;
		_transparentColor = transColor;

		//이미지 초기화에 실패하면
		if (_imageInfo->hBit == NULL) {
			release();
			return E_FAIL;
		}
		return S_OK;
	}

	void BitmapImage::release()
	{
		if (_imageInfo) {
			SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
			DeleteObject(_imageInfo->hBit);
			DeleteDC(_imageInfo->hMemDC);
			SAFE_DELETE_ARRAY(_fileName);
			SAFE_DELETE(_imageInfo);

			_isTransparentEnabled = FALSE;
			_imageInfo = NULL;
		}
	}

	void BitmapImage::render(HDC hdc, int destX, int destY) const
	{
		if (_isTransparentEnabled) {
			//TransparentBlt()
			//TransparentBlt와 차이점은 거의 없다.
			GdiTransparentBlt(
				hdc,				//복사할 대상이 되는 곳(주로 화면 DC)
				destX,				//복사할 이미지의 좌표 x
				destY,				//복사할 이미지의 좌표 y
				_imageInfo->width,	//복사할 이미지의 폭
				_imageInfo->height,	//복사할 이미지의 높이
				_imageInfo->hMemDC,	//복사될 대상 이미지의 DC
				0,					//복사될 대상 이미지의 복사 시작점 x
				0,					//복사될 대상 이미지의 복사 시작점 y
				_imageInfo->width,	//복사될 대상 이미지의 폭
				_imageInfo->height,	//복사될 대상 이미지의 높이
				_transparentColor			//투명으로 처리할 색상
			);
		}
		else {
			BitBlt(hdc,
				destX, destY,
				_imageInfo->width, _imageInfo->height,
				_imageInfo->hMemDC,
				0, 0,
				SRCCOPY);
		}
	}

	void BitmapImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight) const
	{
		if (_isTransparentEnabled) {
			//TransparentBlt와 차이점은 거의 없다.
			GdiTransparentBlt(
				hdc,				//복사할 대상이 되는 곳(주로 화면 DC)
				destX,				//복사할 이미지의 좌표 x
				destY,				//복사할 이미지의 좌표 y
				destWidth,
				destHeight,
				_imageInfo->hMemDC,	//복사될 대상 이미지의 DC
				0,					//복사될 대상 이미지의 복사 시작점 x
				0,					//복사될 대상 이미지의 복사 시작점 y
				_imageInfo->width,	//복사될 대상 이미지의 폭
				_imageInfo->height,	//복사될 대상 이미지의 높이
				_transparentColor			//투명으로 처리할 색상
			);
		}
		else {
			BitBlt(hdc,
				destX, destY,
				destWidth,
				destHeight,
				_imageInfo->hMemDC,
				0, 0,
				SRCCOPY);
		}
	}

	void BitmapImage::render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight) const
	{
		if (_isTransparentEnabled) {
			//TransparentBlt()
			//TransparentBlt와 차이점은 거의 없다.
			GdiTransparentBlt(
				hdc,				//복사할 대상이 되는 곳(주로 화면 DC)
				destX,				//복사할 이미지의 좌표 x
				destY,				//복사할 이미지의 좌표 y
				srcWidth,			//복사할 이미지의 폭
				srcHeight,			//복사할 이미지의 높이
				_imageInfo->hMemDC,	//복사될 대상 이미지의 DC
				srcX,				//복사될 대상 이미지의 복사 시작점 x
				srcY,				//복사될 대상 이미지의 복사 시작점 y
				srcWidth,			//복사될 대상 이미지의 폭
				srcHeight,			//복사될 대상 이미지의 높이
				_transparentColor			//투명으로 처리할 색상
			);
		}
		else {
			BitBlt(hdc,
				destX, destY,
				srcWidth, srcHeight,
				_imageInfo->hMemDC,
				srcX, srcY,
				SRCCOPY);
		}
	}

	void BitmapImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight) const
	{
		if (_isTransparentEnabled) {
			//TransparentBlt()
			//TransparentBlt와 차이점은 거의 없다.
			GdiTransparentBlt(
				hdc,				//복사할 대상이 되는 곳(주로 화면 DC)
				destX,				//복사할 이미지의 좌표 x
				destY,				//복사할 이미지의 좌표 y
				destWidth,	//복사할 이미지의 폭
				destHeight,	//복사할 이미지의 높이
				_imageInfo->hMemDC,	//복사될 대상 이미지의 DC
				srcX,				//복사될 대상 이미지의 복사 시작점 x
				srcY,				//복사될 대상 이미지의 복사 시작점 y
				srcWidth,			//복사될 대상 이미지의 폭
				srcHeight,			//복사될 대상 이미지의 높이
				_transparentColor			//투명으로 처리할 색상
			);
		}
		else {
			//StretchBlt Me.hdc, Picture1.Width, 0, Picture1.Width, Picture1.Height, Picture1.hdc, Picture1.Width, 0, -Picture1.Width, Picture1.Height, SRCCOPY
			StretchBlt(hdc,
				destX, destY,
				destWidth, destHeight,
				_imageInfo->hMemDC,
				srcX, srcY,
				srcWidth, srcHeight, SRCCOPY);
		}
	}

	void BitmapImage::clearImage(COLORREF color)
	{
		SelectObject(_imageInfo->hMemDC, GetStockObject(DC_PEN));
		COLORREF colorOldPen = SetDCPenColor(_imageInfo->hMemDC, color);
		SelectObject(_imageInfo->hMemDC, GetStockObject(DC_BRUSH));
		COLORREF colorOld = SetDCBrushColor(_imageInfo->hMemDC, color);
		Rectangle(_imageInfo->hMemDC, 0, 0, getWidth(), getHeight());
		SetDCBrushColor(_imageInfo->hMemDC, colorOld);
		SetDCPenColor(_imageInfo->hMemDC, colorOldPen);
	}
}