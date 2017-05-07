#include "MathUtils.h"
#include <assert.h>
#include "MathUtils.h"

#define __MY_PI					3.141592654f

namespace SGA {
	bool isEqualFloat(const float& num1, const float& num2, const float& epsilon) {
		return fabs(num1 - num2) <= epsilon;
	}

	bool isEqualfloat(const float& num1, const float& num2, const float& epsilon) {
		return fabs(num1 - num2) <= epsilon;
	}

	//두 지점의 거리를 구한다.
	float getDistance(float startX, float startY, float endX, float endY) {
		float dx, dy;
		dx = startX - endX;
		dy = startY - endY;
		return sqrt(dx*dx + dy*dy);
	}

	//두 지점의 각을 라디안으로 구한다.
	float getangle(float startX, float startY, float endX, float endY) {
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrt(x*x + y*y);

		float angle = acos(x / d);
		if (y > 0) angle = __MY_PI * 2 - angle;
		return angle;
	}

	Point2D operator+(const Point2D& p1, const Point2D& p2) {
		return{ p1.x + p2.x, p1.y + p2.y };
	}

	Point2D operator-(const Point2D& p1, const Point2D& p2) {
		return{ p1.x - p2.x, p1.y - p2.y };
	}

	Point2D operator*(float s, const Point2D& p) {
		return{ s*p.x, s*p.y };
	}

	POINT POINTFLOAT2POINT(const POINTFLOAT & pt)
	{
		return{ (long)pt.x, (long)pt.y };
	}

	POINTFLOAT POINT2POINTFLOAT(const POINT & pt)
	{
		return{ (float)pt.x, (float)pt.y };
	}

	float deg2rad(float deg)
	{
		return deg * 0.01745329252f;
	}

	float rad2deg(float rad)
	{
		return rad * 57.295779513f;
	}

	float norm(const Point2D& p) {
		return sqrt(p.x*p.x + p.y*p.y);
	}

	float dotProduct(const Point2D& p1, const Point2D& p2) {
		return p1.x*p2.x + p1.y*p2.y;
	}

	float crossProduct(const Point2D & v1, const Point2D & v2)
	{
		return v1.x*v2.y - v1.y*v2.x;
	}

	Point2D rotate2D(const Point2D& p, const float& angle) {
		float c = cos(angle), s = sin(angle);
		return{ c*p.x - s*p.y, s*p.x + c*p.y };
	}

	void rotate2D(Point2D & p, const float & angle, const Point2D & anchor)
	{
		Point2D tmp = p - anchor;
		tmp = rotate2D(tmp, angle);
		p = tmp + anchor;
	}

	void getRotatedRECT(const RECT & rect, const float & angle, POINTFLOAT * pt)
	{
		pt[0].x = rect.left;	pt[1].x = rect.right;	pt[2].x = rect.right;		pt[3].x = rect.left;
		pt[0].y = rect.top;		pt[1].y = rect.top;		pt[2].y = rect.bottom;		pt[3].y = rect.bottom;
		POINTFLOAT center;
		center.x = (rect.right + rect.left) / 2;
		center.y = (rect.top + rect.bottom) / 2;

		for (int i = 0; i < 4; i++) {
			rotate2D(pt[i], angle, center);
		}
	}

	void getRotatedRECT(const RECT & rect, const float & angle, POINT * points)
	{
		POINTFLOAT pt[4];
		getRotatedRECT(rect, angle, pt);
		for (int i = 0; i < 4; i++) {
			points[i] = POINTFLOAT2POINT(pt[i]);
		}
	}

	bool isParallel(const Line2D& L1, const Line2D& L2) {
		return isEqualFloat(L1.a*L2.b, L2.a*L1.b, 0.0001);
	}

	bool isVertical(const Line2D& line) {
		if (fabs(line.b) < 0.0001) {
			return true;
		}
		if (fabs(line.a / line.b) > 10000.0) {
			return true;
		}
		return false;
	}

	bool isSegmentsIntersect(const Point2D & a1, const Point2D & a2, const Point2D & b1, const Point2D & b2)
	{
		if (crossProduct(a2 - a1, b1 - a1)*crossProduct(a2 - a1, b2 - a1) >= 0) {
			return false;
		}
		if (crossProduct(b2 - b1, a1 - b1) * crossProduct(b2 - b1, a2 - b1) >= 0) {
			return false;
		}
		return true;
	}

	Point2D getIntersectingPointLineLine(const Line2D& line1, const Line2D& line2) {
		float test = line1.a*line2.b - line2.a*line1.b;
		assert(fabs(test) > 0.00001f);
		float tmp = line1.b*line2.c - line2.b*line1.c;
		return{ tmp / test, -line1.a / line1.b*(tmp / test) - line1.c / line1.b };
	}

	/*
	line1이 수직이면 에러!
	*/
	bool getIntersectingPointLineLine(const Line2D& line1, const Line2D& line2, Point2D& pointOut) {
		float test = line1.a*line2.b - line2.a*line1.b;
		if (fabs(test) < 0.00001f) {
			//line1과 line2가 거의 수평이거나 일치하는 경우
			return false;
		}
		if (fabs(line1.b) < 0.001f) {
			//line1이 수직
			pointOut.x = -line1.c / line1.a;
			pointOut.y = -(line2.c + line2.a*pointOut.x) / line2.b;
		}
		else {
			float tmp = line1.b*line2.c - line2.b*line1.c;
			pointOut = { tmp / test, -line1.a / line1.b*(tmp / test) - line1.c / line1.b };
		}
		return true;
	}

	Point2D getIntersectingPointPointLine(const Point2D& p, const Line2D& line) {
		float tmp = line.a*line.a + line.b*line.b;
		float tmp2 = line.b*p.x - line.a*p.y;
		return{ (line.b*tmp2 - line.a*line.c) / tmp, (-line.a*tmp2 - line.b*line.c) / tmp };
	}

	float getDistancePointLine(const Point2D& p, const Line2D& L) {
		return abs(L.a*p.x + L.b*p.y + L.c) / sqrt(L.a*L.a + L.b*L.b);
	}

	Point2D getInterpolatedPoint(const Point2D& begin, const Point2D& end, float s) {
		return begin + s*(end - begin);
	}

	Point2D getPointOnLine(const Line2D& line, const Point2D& p0, const float& dist) {
		if (isVertical(line)) {
			return{ p0.x, p0.y + dist };
		}
		else {
			float m = -line.a / line.b;
			float deltax = getSign(dist) * sqrt(dist * dist / (1 + m*m));
			float deltay = deltax * m;

			return{ p0.x + deltax, p0.y + deltay };
		}
	}
}