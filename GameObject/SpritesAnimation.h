#pragma once
#include <vector>
#include <Windows.h>
#include "SpriteIface.h"
namespace SGA {
	class Sprite;
	class ClockIface;
	class SpritesAnimation : public SpriteIface
	{
	public:
		SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, int durationMilli, int maxReplayCount = 0);

		virtual ~SpritesAnimation();

		/*
		this를 복사한 객체를 반환한다.
		*/
		SpritesAnimation* clone() const;

		/*
		마지막 스프라이트 교체 시각이후로 _durationMs만큼의 시간이 지나면
		현재 스프라이트를 다음 스프라이트로 교체한다.
		*/
		void update();

		/*
		현재 스프라이트를 drawPosX, drawPosY에 렌더링한다.
		*/
		virtual void render(HDC hdc, int drawPosX, int drawPosY) const;

		/*
		누적 데이터를 리셋하고 첫번재 스프라이트부터 재생한다.
		*/
		void restart();

		/*
		애니메이션에 사용할 시계를 설정한다.
		초기값 : GameWorldClock
		*/
		inline void setClock(const ClockIface* clock) {
			_clock = clock;
		}

		/*
		재생을 시작할 스프라이트의 인덱스를 설정한다.
		*/
		void setCurrentSprite(int spriteIdx);

		/*
		스프라이트 하나당 재생시간(millisec)을 세팅한다.
		*/
		inline void setDuration(int durationMillis) {
			_durationMs = durationMillis;
		}

		inline int getDuration() const {
			return _durationMs;
		}

		/*
		애니메이션 반복 재생 횟수를 설정한다.
		0으로 설정하면 애니메이션을 무한정 반복한다.
		*/
		inline void setMaxReplayCount(int maxReplayCount) {
			_maxReplayCount = maxReplayCount;
		}

		inline int getMaxReplayCount() const{
			return _maxReplayCount;
		}

		/*
		지금까지 총 애니메이션 반복 횟수를 반환한다.
		restart()메서드를 호출하면 리셋된다.
		*/
		inline int getPlayCount() const {
			return _replayCount;
		}

		/*
		정해진 횟수만큼 애니메이션이 플레이되면 true를 반환.
		_maxReplayCount가 0이면 무한반복이기 때문에 항상 false를 반환.
		*/
		inline bool isPlayDone() const {
			if (_maxReplayCount == 0)
				return false;
			if (_replayCount == _maxReplayCount)
				return true;
			return false;
		}

		inline bool isInfinite() const {
			return _maxReplayCount == 0;
		}

		/*
		애니메이션에 사용되는 총 스프라이트 개수를 반환한다.
		*/
		inline int getNSprites() const {
			return _sprites.size();
		}

		inline void setActive() {
			_active = true;
		}

		inline void clearActive() {
			_active = false;
		}

		inline bool isActive() const {
			return _active;
		}
	private:
		std::vector<const SGA::Sprite*> _sprites;
		//현재 재생중인 스프라이트
		int _currentSprite;
		//총 재생 횟수
		int _replayCount;
		//마지막 스프라이트가 바뀐 시각
		unsigned long _lastSwitchTime;
		//스프라이트 전환 주기
		int _durationMs;
		//스프라이트를 다시 재생하는 횟수
		int _maxReplayCount;
		//애니메이션 재생에 사용할 시계
		//default : GameWorldClock
		const ClockIface* _clock;

		bool _active;
	};
}