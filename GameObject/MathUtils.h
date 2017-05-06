#pragma once
#include <cmath>
#include <Windows.h>
#include "Line2D.h"


namespace SGA {
	typedef POINTFLOAT Point2D;
	template <typename T>
	int getSign(T val) {
		if (val > 0)
			return 1;
		if (val < 0)
			return -1;
		return 0;
	}

	Point2D operator+(const Point2D& p1, const Point2D& p2);
	Point2D operator-(const Point2D& p1, const Point2D& p2);
	Point2D operator*(float s, const Point2D& p1);

	POINT POINTFLOAT2POINT(const POINTFLOAT& pt);
	POINTFLOAT POINT2POINTFLOAT(const POINT& pt);


	bool isEqualFloat(const float& num1, const float& num2, const float& epsilon = 0.001f);

	bool isEqualfloat(const float& num1, const float& num2, const float& epsilon = 0.001);

	//�� ������ �Ÿ��� ���Ѵ�.
	float getDistance(float startX, float startY, float endX, float endY);

	//�� ������ ���� �������� ���Ѵ�.
	float getangle(float startX, float startY, float endX, float endY);

	/*
	p�� ���̸� ��ȯ�Ѵ�.
	*/
	float norm(const Point2D& p);

	/*
	�� p1�� p2�� ������ ��ȯ�Ѵ�.
	*/
	float dotProduct(const Point2D& p1, const Point2D& p2);

	/*
	�� p�� ����(0,0)�� ���Ͽ� angle��ŭ ȸ����Ų ���� ��ȯ�Ѵ�.
	*/
	Point2D rotate2D(const Point2D& p, const float& angle);

	void rotate2D(Point2D& p, const float& angle, const Point2D& anchor);

	void getRotatedRECT(const RECT& rect, const float& angle, POINTFLOAT * points);

	/*
	return true if two lines,L1 and L2, are (exactly or almost) parallel.
	return false otherwise.
	*/
	bool isParallel(const Line2D& L1, const Line2D& L2);

	/*
	return true, if 'line' is (almost) vertical.
	*/
	bool isVertical(const Line2D& line);

	/*
	�� ������ ������ line1�� line2�� ������ ������ ��ȯ�Ѵ�.
	�� ������ �������� �ʾƾ� �Ѵ�!
	*/
	Point2D getIntersectingPointLineLine(const Line2D& line1, const Line2D& line2);

	bool getIntersectingPointLineLine(const Line2D& line1, const Line2D& line2, Point2D& pointOut);

	/*
	���� 'line'�� �� p�� ������ 'line'�� �����ϴ� ���� ������ ������ ��ȯ�Ѵ�.
	*/
	Point2D getIntersectingPointPointLine(const Point2D& p, const Line2D& line);

	/*
	return the distance between a point 'p' and a line 'L'.
	*/
	float getDistancePointLine(const Point2D& p, const Line2D& L);

	/*
	s=0.0      : begin
	s=1.0      : end
	0.0<s<1.0  : interpolate
	s>1.0      : extrapolate
	s<0.0      : negative extrapolate
	*/
	Point2D getInterpolatedPoint(const Point2D& begin, const Point2D& end, float s);

	/*
	���� 'line'���� �ְ� �� p0�� dist��ŭ�� �Ÿ��� �ִ� ���� ��ȯ�Ѵ�.
	p0���� dist��ŭ ������ ���� �� 2���̴�.
	if 'dist' > 0
		p0���� �����ʿ� �ִ� ���� ��ȯ.
	else if 'dist' < 0
		p0���� ���ʿ� �ִ� ���� ��ȯ.
	else
		p0�� ��ȯ
	*/
	Point2D getPointOnLine(const Line2D& line, const Point2D& p0, const float& dist);
}