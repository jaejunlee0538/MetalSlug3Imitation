#pragma once
#include "SingletonBase.h"
#include <random>
#include <time.h>
namespace SGA {
	class RandomFunction : public SingletonBase<RandomFunction>
	{
	public:
		RandomFunction() {
			srand(time(0));
			//srand(GetTickCount());
		}

		~RandomFunction() {

		}

		int getInt(int maxNum) { return rand() % (maxNum + 1); }
		int getIntFromTo(int minNum, int maxNum) { return minNum + rand() % (maxNum - minNum + 1); }

		/*
		[0.0, 1.0] 범위의 임의의 실수를 반환한다.
		*/
		float getFloat(void) {
			return (float)rand() / RAND_MAX;
			//return (rand() % 1000) / 999.0f;
		}

		/*
		[0, num] 범위의 임의의 실수를 반환한다.
		*/
		float getFloat(float num) {
			return ((float)rand() / RAND_MAX) * num;
		}

		/*
		[fromFloat, toFloat] 범위의 임의의 실수를 반환한다.
		*/
		float getFloatFromTo(float fromFloat, float toFloat) {
			if (fromFloat < toFloat) {
				return fromFloat + getFloat(toFloat - fromFloat);
			}
			else {
				return toFloat + getFloat(fromFloat - toFloat);
			}
		}

		bool getBoolRandom() {
			return getInt(50) % 2 == 0;
		}
	};
}