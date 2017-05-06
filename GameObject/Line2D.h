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
	직선의 방정식이 거의 수직이면 true를 반환.
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
	ax+by+c=0에 해당하는 Line2D를 반환
	*/
	static Line2D fromGeneralForm(float a, float b, float c);
	/*
	두점 p1, p2를 지나는 직선의 방정식을 반환
	*/
	static Line2D fromTwoPoints(float x1, float y1, float x2, float y2);
	/*
	점 p를 지나고 기울기가 m인 직선의 방정식을 반환
	*/
	static Line2D fromPointSlope(float x, float y, float m);

	//ax+by+c=0
	float a, b, c;
};
