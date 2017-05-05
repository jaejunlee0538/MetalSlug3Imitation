#pragma once
#include <Windows.h>
#include <math.h>
#include <assert.h>
#include <utility>
namespace SGA {
	/*
	p가 rect의 표면 내에 있다면 true를 반환한다. 
	*/
	template <typename RECTType, typename POINTType>
	inline bool isPointInRect(const RECTType& rect, const POINTType& p) {
		return rect.left<p.x && rect.right>p.x && rect.top<p.y&&rect.bottom>p.y;
	}

	/*

	*/
	template <typename RECTType, typename POINTType>
	inline bool isPointOutRect(const RECTType& rect, const POINTType& p, decltype(p.x) epsilon) {
		return (rect.left-epsilon) > p.x && (rect.right+epsilon)<p.x 
			&& (rect.top-epsilon)>p.y&&(rect.bottom+ epsilon)<p.y;
	}

	/*
	p가 중심이 centerOfCircle이고 반지름이 R인 원의 표면 내에 있다면 true를 반환한다.
	*/
	template <typename POINTType>
	inline bool isPointInCircle(const POINTType& center, float R, const POINTType& p) {
		float dx, dy;
		dx = center.x - p.x;
		dy = center.y - p.y;
		return (dx*dx + dy*dy) < R*R;
	}
	
	/*
	RECT로 표현되는 원 circle의 내에 점 p가 있다면 true를 반환한다.
	*/
	template <typename RECTType, typename POINTType>
	inline bool isPointInCircle(RECTType circle, POINTType p) {
		float dx, dy;
		float R = (circle.right - circle.left)*0.5f;
		//원의 중심점에서 p로 항하는 벡터
		dx = p.x - (circle.right + circle.left) * 0.5f;
		dy = p.y - (circle.bottom + circle.top) * 0.5f;
		return (dx * dx + dy * dy) < R*R;
	}

	/*
	RECT로 표현되는 타원 ellipse 내에 점 p가 있다면 true를 반환한다.
	*/
	inline bool isPointInEllipse(RECT ellipse, POINT p) {
		float rx, ry;
		float cx, cy;
		float dx, dy;
		//타원의 x,y 반지름 계산
		rx = (ellipse.right - ellipse.left) * 0.5f;
		ry = (ellipse.bottom - ellipse.top) * 0.5f;
		//타원의 중심점 계산
		cx = (ellipse.right + ellipse.left) * 0.5f;
		cy = (ellipse.bottom + ellipse.top) * 0.5f;
		//p->타원 중심을 향하는 벡터를 rx,ry로 정규화시킨다.
		dx = (p.x - cx) / rx;
		dy = (p.y - cy) / ry;
		return (dx * dx + dy * dy) < 1.0f;
	}

	/*
	rectInner가 rectOuter에 완전히 겹쳐져 있으면 true를 반환한다.
	*/
	template <typename RECTType>
	inline bool isRectInRect(const RECTType& rectInner, const RECTType& rectOuter) {
		return rectInner.left > rectOuter.left
			&& rectInner.right < rectOuter.right
			&& rectInner.top > rectOuter.top
			&& rectInner.bottom < rectOuter.bottom;
	}
	/*
	ellipse가 rect에 완전히 겹쳐져 있으면 true를 반환한다.
	*/
	inline bool isEllipseInRect(const RECT& ellipse, const RECT& rect) {
		return ellipse.left > rect.left
			&& ellipse.right < rect.right
			&& ellipse.top > rect.top
			&& ellipse.bottom < rect.bottom;
	}

	/*

	*/
	inline bool isRectInEllipse(const RECT& rect, const RECT& ellipse) {
		//rect의 모든 점이 ellipse에 들어있는지 확인한다.
		POINT p;
		p.x = rect.left; p.y = rect.top;
		if (!isPointInEllipse(ellipse, p))	return false;
		p.x = rect.right;
		if (!isPointInEllipse(ellipse, p))	return false;
		p.y = rect.bottom;
		if (!isPointInEllipse(ellipse, p))	return false;
		p.x = rect.left;
		if (!isPointInEllipse(ellipse, p))	return false;
		return true;
	}

	/*
	circle가 rect에 완전히 겹쳐져 있으면 true를 반환한다.
	*/
	inline bool isCircleInRect(const RECT& circle, const RECT& rect) {
		return circle.left > rect.left
			&& circle.right < rect.right
			&& circle.top > rect.top
			&& circle.bottom < rect.bottom;
	}

	/*
	TODO : 
	*/
	inline bool isCircleInCircle(const RECT& circleInner, const RECT& circleOuter) {
		return false;
	}

	///////////////사각형과 사각형 사이의 충돌///////////////////////////////////////////////////////////////
	/*
	rect1과 rect2가 충돌한다면(완전히 또는 조금이라도 겹친다면) true를 반환한다.
	*/
	template <typename RECTType>
	inline bool isCollideRectRect(const RECTType& rect1, const RECTType& rect2) {
		return rect1.left < rect2.right && rect1.right > rect2.left && rect1.top < rect2.bottom && rect1.bottom > rect2.top;
	}

	///////////////사각형과 원 사이의 충돌///////////////////////////////////////////////////////////////
	/*
	rect와 중심이 center이고 반지름이 R인 원과 충돌한다면(완전히 또는 조금이라도 겹친다면) true를 반환한다.
	*/
	template <typename RECTType,typename POINTType>
	inline bool isCollideRectCircle(RECTType rect, POINTType center, float R) {
		//TODO : 이조건을 사용하면 잘못된 충돌이 검출된다.

		if (center.x >= rect.left && center.x <= rect.right || center.y >= rect.top && center.y <= rect.bottom) {
			rect.left -= R;
			rect.right += R;
			rect.top -= R;
			rect.bottom += R;
			return isPointInRect(rect, center);
		}
		else {
			POINTFLOAT p;
			p.x = rect.left; p.y = rect.top;

			if (isPointInCircle(center, R, p))	return true;
			p.x = rect.right;
			if (isPointInCircle(center, R, p))	return true;
			p.y = rect.bottom;
			if (isPointInCircle(center, R, p)) return true;
			p.x = rect.left;
			if (isPointInCircle(center, R, p))return true;
			return false;
		}
	}

	/*
	rect와 중심이 center이고 반지름이 R인 원과 충돌한다면(완전히 또는 조금이라도 겹친다면) true를 반환한다.
	*/
	template <typename RECTType>
	inline bool isCollideRectCircle(const RECTType& rect, const RECTType& circle) {
		POINTFLOAT c{ (circle.left + circle.right) / 2.0f, (circle.bottom + circle.top) / 2.0f };
		float r = (circle.bottom - circle.top) / 2.0f;
		return isCollideRectCircle(rect, c, r);
	}


	///////////////사각형과 타원 사이의 충돌///////////////////////////////////////////////////////////////
	/*
	
	*/
	template <typename RECTType>
	inline bool isCollideRectEllipse(RECTType rect, RECTType ellipse) {
		float scale = (ellipse.bottom - ellipse.top) / (float)(ellipse.right - ellipse.left);
		POINTFLOAT centerEllipse;
		centerEllipse.x = (ellipse.left + ellipse.right) / 2.0f;
		centerEllipse.y = (ellipse.top + ellipse.bottom) / 2.0f;
		ellipse.left -= centerEllipse.x;
		ellipse.top -= centerEllipse.y;
		ellipse.right -= centerEllipse.x;
		ellipse.bottom -= centerEllipse.y;
		rect.left -= centerEllipse.x;
		rect.top -= centerEllipse.y;
		rect.right -= centerEllipse.x;
		rect.bottom -= centerEllipse.y;
		rect.left *= scale;
		rect.right *= scale;
		ellipse.left *= scale;
		ellipse.right *= scale;
		centerEllipse.x = 0.0f;
		centerEllipse.y = 0.0f;
		return isCollideRectCircle(rect, centerEllipse, (ellipse.bottom - ellipse.top) / 2.0f);
	}
	///////////////원과 원 사이의 충돌///////////////////////////////////////////////////////////////
	/*
	circle1과 circle2가 충돌하면 true를 반환한다.
	*/
	template <typename RECTType>
	inline bool isCollideCircleCircle(const RECTType& circle1, const RECTType& circle2) {
		POINTFLOAT dxy;
		dxy.x = ((circle1.left + circle1.right) - (circle2.left + circle2.right)) / 2.0f;
		dxy.y = ((circle1.top + circle1.bottom) - (circle2.top + circle2.bottom)) / 2.0f;
		float d = (circle1.right - circle1.left + circle2.right - circle2.left) / 2.0f;//두 반지름의 함
		return (dxy.x*dxy.x + dxy.y*dxy.y) < d*d;
	}

	/*
	중심이 center1이고 반지름이 R1인 원1과 중심이 center2이고 반지름이 R2인 원2와의 충돌 검사
	*/
	inline bool isCollideCircleCircle(const POINT& center1, const int R1, const POINT& center2, const int R2) {
		POINT dxy{ center2.x - center1.x, center2.y - center1.y };
		int d = R1+R2;//두 반지름의 함
		return (dxy.x*dxy.x + dxy.y*dxy.y) < d*d;
	}

	/*
	circle1과 circle2가 충돌하고 있을 때 충돌을 해제하기 위해 circle1을 얼마나 이동시켜야 하는지 계산한다.
	*/
	template <typename RECTType, typename POINTTYpe>
	inline POINTTYpe getCollisionVectorCircleCircle(const RECTType& circle1, const RECTType& circle2) {
		float dx, dy;
		POINTTYpe vec;
		dx = ((circle1.left + circle1.right) - (circle2.left + circle2.right)) * 0.5f;
		dy = ((circle1.top + circle1.bottom) - (circle2.top + circle2.bottom)) * 0.5f;
		float d1 = (circle1.right - circle1.left + circle2.right - circle2.left) * 0.5f;//두 반지름의 합
		float d2 = sqrt(dx*dx + dy*dy);//두 중심점 사이의 실제 거리
		if (d2 == 0.0f) {
			//두 원이 완전히 겹쳐버리는 상황.
			//circle1을 어느쪽으로 밀어야할지 알수없음...
			vec.x = d1;
			vec.y = 0;
		}
		else {
			vec.x = dx * (d1 - d2) / d2;
			vec.y = dy * (d1 - d2) / d2;
		}
		return vec;
	}

	/*
	두 원이 접하는 선과 일치하는 벡터를 반환한다.
	*/
	template <typename RECTType, typename POINTTYpe>
	inline POINTTYpe getCollisionLineCircleCircle(const RECTType& circle1, const RECTType& circle2) {
		//TODO : 
		float dx, dy;
		POINTTYpe vec;
		dx = ((circle1.left + circle1.right) - (circle2.left + circle2.right)) * 0.5f;
		dy = ((circle1.top + circle1.bottom) - (circle2.top + circle2.bottom)) * 0.5f;
		float d1 = (circle1.right - circle1.left + circle2.right - circle2.left) * 0.5f;//두 반지름의 합
		float d2 = sqrt(dx*dx + dy*dy);//두 중심점 사이의 실제 거리
		if (d2 == 0.0f) {
			//두 원이 완전히 겹쳐버리는 상황.
			//circle1을 어느쪽으로 밀어야할지 알수없음...
			vec.x = d1;
			vec.y = 0;
		}
		else {
			vec.x = dx * (d1 - d2) / d2;
			vec.y = dy * (d1 - d2) / d2;
		}
		return vec;
	}

	/*
	rectOuter에 포함된 사각형 rectInner가 rectOuter의 표면과 충돌한다면 true를 반환한다.
	*/
	inline bool isCollideRectInsideRect(const RECT& rectInnner, const RECT& rectOuter) {
		if (rectInnner.left < rectOuter.left)		return true;
		if (rectInnner.right > rectOuter.right)		return true;
		if (rectInnner.top < rectOuter.top)			return true;
		if (rectInnner.bottom > rectOuter.bottom)	return true;
		return false;
	}

	/*
	isCollideRectInsideRect(rectInnner, rectOutter)가 true를 반환할 때,
	rectInner를 반환되는 POINT만큼 x,y방향으로 이동시키면 충돌을 해제할 수 있다.
	*/
	inline POINT getCollisionVectorRectInsideRect(const RECT& rectInnner, const RECT& rectOuter) {
		POINT vec = { 0,0 };
		if (rectInnner.left < rectOuter.left)	
			vec.x = rectOuter.left - rectInnner.left;//왼쪽에서 충돌
		else if(rectInnner.right > rectOuter.right)
			vec.x = rectOuter.right - rectInnner.right;//오른쪽에서 충돌
		if (rectInnner.top < rectOuter.top)
			vec.y = rectOuter.top - rectInnner.top;//위에서 충돌
		else if (rectInnner.bottom > rectOuter.bottom)
			vec.y = rectOuter.bottom - rectInnner.bottom;//아래에서 충돌
		return vec;
	}

	/*
	rectOuter에 포함된 원 circleInner가 rectOuter의 표면과 충돌한다면 true를 반환한다.
	*/
	inline bool isCollideCircleInsideRect(const RECT& circleInner, const RECT& rectOuterOuter) {
		return isCollideRectInsideRect(circleInner, rectOuterOuter);
	}

	/*
	isCollideCircleInsideRect(circleInner, rectOutter)가 true를 반환할 때,
	circleInner를 반환되는 POINT만큼 x,y방향으로 이동시키면 충돌을 해제할 수 있다.
	*/
	inline POINT getCollisionVectorCircleInsideRect(const RECT& circleInner, const RECT& rectOuter) {
		POINT vec = { 0,0 };
		if (circleInner.left < rectOuter.left)
			vec.x = rectOuter.left - circleInner.left;//왼쪽에서 충돌
		else if (circleInner.right > rectOuter.right)
			vec.x = rectOuter.right - circleInner.right;//오른쪽에서 충돌
		if (circleInner.top < rectOuter.top)
			vec.y = rectOuter.top - circleInner.top;//위에서 충돌
		else if (circleInner.bottom > rectOuter.bottom)
			vec.y = rectOuter.bottom - circleInner.bottom;//아래에서 충돌
		return vec;
	}

	inline bool isCollideEllipseInsideRect(const RECT& ellipseInner, const RECT& rectOuter) {
		return isCollideRectInsideRect(ellipseInner, rectOuter);
	}

	inline POINT getCollisionVectorEllipseInsideRect(const RECT& ellipseInner, const RECT& rectOuter) {
		POINT vec = { 0,0 };
		if (ellipseInner.left < rectOuter.left)
			vec.x = rectOuter.left - ellipseInner.left;//왼쪽에서 충돌
		else if (ellipseInner.right > rectOuter.right)
			vec.x = rectOuter.right - ellipseInner.right;//오른쪽에서 충돌
		if (ellipseInner.top < rectOuter.top)
			vec.y = rectOuter.top - ellipseInner.top;//위에서 충돌
		else if (ellipseInner.bottom > rectOuter.bottom)
			vec.y = rectOuter.bottom - ellipseInner.bottom;//아래에서 충돌
		return vec;
	}
	
	template <typename RECTType>
	inline POINTFLOAT getTangentLineCircleCircle(const RECTType& rect1, const RECTType& rect2) {
		POINTFLOAT vec = { (rect1.left+rect1.right)/2 - (rect2.left+rect2.right)/2, 
			(rect1.top + rect1.bottom) / 2 - (rect2.top + rect2.bottom) / 2 };
		float len = sqrt(vec.x*vec.x + vec.y*vec.y);
		assert(len > 0.0001f);
		vec.x /= len;
		vec.y /= len;
		return{ vec.y, -vec.x };
	}

	/*
	inputVec가 surface에 입사했을 때 반사되어서 나가는 벡터를 계산하여 반환한다.
	*/
	inline POINTFLOAT getReflectedVector(POINTFLOAT inputVec, POINTFLOAT surface) {
		float len = sqrt(surface.x*surface.x + surface.y*surface.y);
		assert(len > 0.0001f);
		surface.x /= len;
		surface.y /= len;
		float dotProd = inputVec.x*surface.x + inputVec.y*surface.y;
		POINTFLOAT parl{ surface.x*dotProd, surface.y*dotProd };
		POINTFLOAT vert{ inputVec.x - parl.x, inputVec.y - parl.y };
		return{ parl.x - vert.x, parl.y - vert.y };
	}
	/*

	*/
	template <typename RECTType>
	std::pair<POINTFLOAT, POINTFLOAT> getVelocityAfterCollisionCircleCircle(const RECTType& circle1, const RECTType& circle2, 
		const POINTFLOAT& vel1, const POINTFLOAT& vel2) {
		std::pair<POINTFLOAT, POINTFLOAT> reflectedVelocity;
		POINTFLOAT tangent = SGA::getTangentLineCircleCircle<RECTType>(circle1, circle2);
		reflectedVelocity.first= SGA::getReflectedVector(vel1, tangent);
		reflectedVelocity.second = SGA::getReflectedVector(vel2, tangent);
		return reflectedVelocity;
	}
}

