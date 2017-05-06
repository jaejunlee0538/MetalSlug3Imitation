#pragma once
#include <math.h>
#include <Windows.h>
struct Line2D {
	Line2D() :a(0.0f), b(0.0f), c(0.0f) {

	}

	/*
	A line representing ax+by+c=0.
	*/
	Line2D(float a, float b, float c)
		:a(a), b(b), c(c) {

	}

	/*
	������ �������� ���� �����̸� true�� ��ȯ.
	*/
	bool isVertical() const {
		if (fabs(b) < 0.0001) {
			return true;
		}
		if (fabs(a / b) > 10000.0) {
			return true;
		}
		return false;
	}

	/*
	ax+by+c=0�� �ش��ϴ� Line2D�� ��ȯ
	*/
	static Line2D fromGeneralForm(float a, float b, float c);
	/*
	���� p1, p2�� ������ ������ �������� ��ȯ
	*/
	static Line2D fromTwoPoints(float x1, float y1, float x2, float y2);
	/*
	�� p�� ������ ���Ⱑ m�� ������ �������� ��ȯ
	*/
	static Line2D fromPointSlope(float x, float y, float m);

	//ax+by+c=0
	float a, b, c;
};
