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
		//��Ʈ�� ��ü �����ϱ� ���� Window Handle�� �ݵ�� ������ ��
		//BitmapImage::setHWND(hWnd);
		assert(BitmapImage::_hWnd != 0);
	}

	BitmapImage::~BitmapImage()
	{
		//�ݵ�� �������� release�Ұ�!
		//�ı��ڿ��� �ϰ� �ұ�?
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
		//���Ҵ� ����
		if (_imageInfo != NULL) release();

		//DC ���´�
		HDC hdc = GetDC(BitmapImage::_hWnd);

		_imageInfo = new IMAGE_INFO;
		//��Ʈ�� ����� ���ؼ� �޸� DC�� ����� �ش�
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//���ϰ���̸�
		_fileName = NULL;

		//���� DC �����Ѵ�
		ReleaseDC(_hWnd, hdc);

		//���� �÷� ����!
		_transparentColor = FALSE;

		//�̹��� �ʱ�ȭ�� �����ϸ�..
		if (_imageInfo->hBit == NULL)
		{
			release();
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT BitmapImage::init(const TCHAR * fileName, int width, int height, BOOL tran, COLORREF transColor)
	{
		//��ΰ��� ������
		if (fileName == NULL) return E_FAIL;

		//���Ҵ� ����
		if (_fileName != NULL) release();

		HDC hdc = GetDC(BitmapImage::_hWnd);
		_imageInfo = new IMAGE_INFO();
		//��Ʈ�� ����� ���ؼ� �޸� DC�� ����� �ش�.
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//���� ��� ����
		int len = _tcslen(fileName);
		_fileName = new TCHAR[len + 1];
		_tcscpy_s(_fileName, len + 1, fileName);

		ReleaseDC(_hWnd, hdc);

		//���� �÷� ����
		_isTransparentEnabled = tran;
		_transparentColor = transColor;

		//�̹��� �ʱ�ȭ�� �����ϸ�
		if (_imageInfo->hBit == NULL) {
			release();
			return E_FAIL;
		}
		return S_OK;
	}

	HRESULT BitmapImage::init(const TCHAR * fileName, BOOL tran, COLORREF transColor)
	{
		//��ΰ��� ������
		if (fileName == NULL) return E_FAIL;

		//���Ҵ� ����
		if (_fileName != NULL) release();

		HDC hdc = GetDC(BitmapImage::_hWnd);
		_imageInfo = new IMAGE_INFO();
		//��Ʈ�� ����� ���ؼ� �޸� DC�� ����� �ش�.
		_imageInfo->hMemDC = CreateCompatibleDC(hdc);
		//���� �̹��� ũ��� �̹����� �ε��Ѵ�.
		_imageInfo->hBit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		//�о���� �̹��� ������ ���� ũ�⸦ �˾Ƴ���.
		BITMAP bmp = { 0 };
		GetObject(_imageInfo->hBit, sizeof(bmp), &bmp);
		_imageInfo->width = bmp.bmWidth;
		_imageInfo->height = bmp.bmHeight;

		//���� ��� ����
		int len = _tcslen(fileName);
		_fileName = new TCHAR[len + 1];
		_tcscpy_s(_fileName, len + 1, fileName);

		ReleaseDC(_hWnd, hdc);

		//���� �÷� ����
		_isTransparentEnabled = tran;
		_transparentColor = transColor;

		//�̹��� �ʱ�ȭ�� �����ϸ�
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
			//TransparentBlt�� �������� ���� ����.
			GdiTransparentBlt(
				hdc,				//������ ����� �Ǵ� ��(�ַ� ȭ�� DC)
				destX,				//������ �̹����� ��ǥ x
				destY,				//������ �̹����� ��ǥ y
				_imageInfo->width,	//������ �̹����� ��
				_imageInfo->height,	//������ �̹����� ����
				_imageInfo->hMemDC,	//����� ��� �̹����� DC
				0,					//����� ��� �̹����� ���� ������ x
				0,					//����� ��� �̹����� ���� ������ y
				_imageInfo->width,	//����� ��� �̹����� ��
				_imageInfo->height,	//����� ��� �̹����� ����
				_transparentColor			//�������� ó���� ����
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
			//TransparentBlt�� �������� ���� ����.
			GdiTransparentBlt(
				hdc,				//������ ����� �Ǵ� ��(�ַ� ȭ�� DC)
				destX,				//������ �̹����� ��ǥ x
				destY,				//������ �̹����� ��ǥ y
				destWidth,
				destHeight,
				_imageInfo->hMemDC,	//����� ��� �̹����� DC
				0,					//����� ��� �̹����� ���� ������ x
				0,					//����� ��� �̹����� ���� ������ y
				_imageInfo->width,	//����� ��� �̹����� ��
				_imageInfo->height,	//����� ��� �̹����� ����
				_transparentColor			//�������� ó���� ����
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
			//TransparentBlt�� �������� ���� ����.
			GdiTransparentBlt(
				hdc,				//������ ����� �Ǵ� ��(�ַ� ȭ�� DC)
				destX,				//������ �̹����� ��ǥ x
				destY,				//������ �̹����� ��ǥ y
				srcWidth,			//������ �̹����� ��
				srcHeight,			//������ �̹����� ����
				_imageInfo->hMemDC,	//����� ��� �̹����� DC
				srcX,				//����� ��� �̹����� ���� ������ x
				srcY,				//����� ��� �̹����� ���� ������ y
				srcWidth,			//����� ��� �̹����� ��
				srcHeight,			//����� ��� �̹����� ����
				_transparentColor			//�������� ó���� ����
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
			//TransparentBlt�� �������� ���� ����.
			GdiTransparentBlt(
				hdc,				//������ ����� �Ǵ� ��(�ַ� ȭ�� DC)
				destX,				//������ �̹����� ��ǥ x
				destY,				//������ �̹����� ��ǥ y
				destWidth,	//������ �̹����� ��
				destHeight,	//������ �̹����� ����
				_imageInfo->hMemDC,	//����� ��� �̹����� DC
				srcX,				//����� ��� �̹����� ���� ������ x
				srcY,				//����� ��� �̹����� ���� ������ y
				srcWidth,			//����� ��� �̹����� ��
				srcHeight,			//����� ��� �̹����� ����
				_transparentColor			//�������� ó���� ����
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