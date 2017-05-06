#include "Line2D.h"

Line2D Line2D::fromGeneralForm(float a, float b, float c) {
	return Line2D(a, b, c);
}

Line2D Line2D::fromTwoPoints(float x1, float y1, float x2, float y2) {
	//return Line2D(p2.x - p1.y, -(p2.x - p1.x), p2.x*p1.y - p1.x*p2.y);
	return Line2D(y2 - y1, -(x2 - x1), (x2 - x1)*y2 - (y2 - y1)*x2);
}

Line2D Line2D::fromPointSlope(float x, float y, float m) {
	return Line2D(m, -1.0, y - m*x);
}