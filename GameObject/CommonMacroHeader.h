#pragma once
#include <Windows.h>
#include <vector>
#include "RandomFunction.h"
#define _USE_MATH_DEFINES
#include <math.h>
namespace SGA {
	template <typename POINTType>
	inline POINTFLOAT getNormalized(const POINTType& point) {
		float len = sqrt(point.x*point.x + point.y*point.y);
		assert(len > 0.000001f);
		return{ point.x / len, point.y / len };
	}

	template <typename POINTType>
	inline float getLength(const POINTType& pt) {
		return sqrt(pt.x*pt.x + pt.y*pt.y);
	}

	template <typename POINTType>
	inline POINTType getCenter(const POINTType& p1, const POINTType& p2) {
		return{ (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
	}

	template <typename POINTType, typename RECTType>
	inline POINTType getCenter(const RECTType& rect) {
		POINTType center;
		center.x = (rect.right + rect.left) / 2.0f;
		center.y = (rect.bottom + rect.top) / 2.0f;
		return center;
	}

	template <typename POINTType>
	inline float getDistance(const POINTType& p1, const POINTType& p2) {
		POINTType dp;
		dp.x = p1.x - p2.x;
		dp.y = p1.y - p2.y;
		return sqrt(dp.x * dp.x + dp.y * dp.y);
	}

	template <typename RECTType>
	inline POINTFLOAT getWidthHeight(const RECTType& rect) {
		return{ rect.right - rect.left, rect.bottom - rect.top };
	}

	template <typename POINTType, typename T>
	inline POINTType makePoint(T x, T y) {
		POINTType pt = { x,y };
		return pt;
	}

	template <typename RECTType, typename T>
	inline RECTType makeRect(T xLT, T yLT, T width, T height) {
		RECTType rect = { xLT, yLT, xLT + width, yLT + height };
		return rect;
	}

	template <typename RECTType, typename T>
	inline RECTType makeRectCenter(T x, T y, T width, T height) {
		//게임만들때는 무조건 중심을 기준으로 생각하자. 그게 편하다.
		RECTType rect = { x - width / 2.0f, y - height / 2.0f, x + width / 2.0f, y + height / 2.0f };
		return rect;
	}

	template <typename RECTType, typename T>
	inline void moveRect(RECTType& rect, T dx, T dy) {
		rect.left += dx;
		rect.right += dx;
		rect.bottom += dy;
		rect.top += dy;
	}

	template <typename RECTType, typename POINTType>
	inline void moveRect(RECTType& rect, POINTType pt) {
		rect.left += pt.x;
		rect.right += pt.x;
		rect.bottom += pt.y;
		rect.top += pt.y;
	}

	template <typename RECTType, typename T>
	inline void moveRect(RECTType& rect, T dx, T dy, T dt) {
		dx *= dt;
		dy *= dt;
		rect.left += dx;
		rect.right += dx;
		rect.bottom += dy;
		rect.top += dy;
	}

	template <typename RECTType, typename POINTTYpe>
	inline void moveRect(RECT& rect, POINTTYpe velocity, float dt) {
		int dx, dy;
		dx = velocity.x * dt;
		dy = velocity.y * dt;
		moveRect(rect, dx, dy);
	}

	/*
	rect의 중심점이 (cx,cy)가 되도록 이동시킨다.
	*/
	template <typename RECTType, typename T>
	inline void moveRectCenterTo(RECTType& rect, T cx, T cy) {
		float dx = cx - (rect.right + rect.left)*0.5;
		float dy = cy - (rect.top + rect.bottom)*0.5;
		rect.left += dx;
		rect.right += dx;
		rect.top += dy;
		rect.bottom += dy;
	}

	inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2) {
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}

	inline void drawLines(HDC hdc, const std::vector<POINT>& pts) {
		std::vector<POINT>::const_iterator it;
		int i = 0;
		for (it = pts.cbegin(); it != pts.cend(); ++it, ++i) {
			if (i == 0) {
				MoveToEx(hdc, it->x, it->y, NULL);
			}
			else {
				LineTo(hdc, it->x, it->y);
				//MoveToEx(hdc, it->x, it->y, NULL);
			}
		}
	}

	inline COLORREF changeDCBrushColor(HDC hdc, COLORREF newColor) {
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		COLORREF colorOld = GetDCBrushColor(hdc);
		SetDCBrushColor(hdc, newColor);
		return colorOld;
	}

	//inline void drawEllipse(HDC hdc, int x, int y, int width, int height) {
	//	Ellipse(hdc, x, y, x + width, y + height);
	//}
	//
	//inline void drawRectangle(HDC hdc, int x, int y, int width, int height) {
	//	Rectangle(hdc, x, y, x + width, y + height);
	//}
	//
	//inline void drawRectangle(HDC hdc, const RECT& rect) {
	//	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	//}
	//
	//inline void drawRectangleCenter(HDC hdc, int x, int y, int width, int height) {
	//	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
	//}

	inline void drawRectangle(HDC hdc, int x, int y, int width, int height) {
		Rectangle(hdc, x, y, x + width, y + height);
	}

	/*
	x,y : left-top 좌표
	width, height : 사각형의 폭과 높이
	*/
	inline void drawRectangle(HDC hdc, int x, int y, int width, int height, COLORREF color) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Rectangle(hdc, x, y, x + width, y + height);
		changeDCBrushColor(hdc, colorOld);
	}

	/*
	x,y : left-top 좌표
	width, height : 사각형의 폭과 높이
	*/
	inline void drawRectangle(HDC hdc, const RECT& rect, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		changeDCBrushColor(hdc, colorOld);
	}

	/*
	rect를 pt에 상대 좌표로 화면에 그린다.
	*/
	inline void drawRelativeRectangle(HDC hdc, RECT rect, const POINT& pt, COLORREF color = RGB(255, 255, 255)) {
		rect.left -= pt.x;
		rect.right -= pt.x;//작성중
		rect.bottom -= pt.x;//작성중
		rect.top -= pt.x;//작성중
		drawRectangle(hdc, rect, color);
	}

	/*
	localRect를 movement만큼 이동시킨 RECT를 화면에 그린다
	*/
	inline void drawRectangleMoved(HDC hdc, RECT localRect, POINT movement, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Rectangle(hdc, 
			localRect.left+ movement.x, 
			localRect.top + movement.y, 
			localRect.right + movement.x, 
			localRect.bottom + movement.y);
		changeDCBrushColor(hdc, colorOld);
	}

	/*
	localRect를 movement만큼 이동시킨 RECT를 화면에 그린다.
	*/
	inline void drawEllipseMoved(HDC hdc, RECT localRect, POINT movement, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Ellipse(hdc,
			localRect.left + movement.x,
			localRect.top + movement.y,
			localRect.right + movement.x,
			localRect.bottom + movement.y);
		changeDCBrushColor(hdc, colorOld);
	}

	/*
	buffer의 텍스트를 pos에 나타낸다.
	*/
	inline void drawText(HDC hdc, const TCHAR* buffer, size_t len,  POINT pos) {
		int prevMode = SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, pos.x, pos.y, buffer, len);
		prevMode = SetBkMode(hdc, prevMode);
	}

	inline void drawTextCenter(HDC hdc, const TCHAR* buffer, size_t len, POINT pos) {
		int prevMode = SetBkMode(hdc, TRANSPARENT);
		UINT prevAlign = SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, pos.x, pos.y, buffer, len);
		SetTextAlign(hdc, prevAlign);
		prevMode = SetBkMode(hdc, prevMode);
	}

	/*
	cx,cy : 사각형의 중심 좌표
	width, height : 사각형의 폭과 높이
	*/
	inline void drawRectangleCenter(HDC hdc, int cx, int cy, int width, int height, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Rectangle(hdc, cx - width / 2, cy - height / 2, cx + width / 2, cy + height / 2);
		changeDCBrushColor(hdc, colorOld);
	}


	/*
	x,y : left-top 좌표
	width, height : 타원을 포함하는 사각형의 폭과 높이
	*/
	inline void drawEllipse(HDC hdc, int x, int y, int width, int height, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Ellipse(hdc, x, y, x + width, y + height);
		changeDCBrushColor(hdc, colorOld);
	}

	inline void drawEllipse(HDC hdc, const RECT& rect, COLORREF color = RGB(255, 255, 255)) {
		COLORREF colorOld = changeDCBrushColor(hdc, color);
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		changeDCBrushColor(hdc, colorOld);
	}

	inline POINT parseMousePosition(LPARAM param) {
		return{ LOWORD(param), HIWORD(param) };
	}

	inline COLORREF getRandomRGB() {
		return RGB(RandomFunction::getSingleton()->getInt(256), RandomFunction::getSingleton()->getInt(256), RandomFunction::getSingleton()->getInt(256));
	}

	/*
	object의 좌표를 reference의 TopLeft에 상대좌표로 변환한다.
	*/
	inline RECT getRelativeRect(const RECT& object, const RECT& reference) {
		return{ object.left - reference.left,
			object.top - reference.top,
		object.right - reference.left,
		object.bottom - reference.top };
	}
}