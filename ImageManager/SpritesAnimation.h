#pragma once
#include <vector>
#include <Windows.h>

namespace SGA {
	class Sprite;

	class SpritesAnimation
	{
	public:
		SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, int durationMilli, int maxReplayCount = 0, bool mirrored=false);

		~SpritesAnimation();

		/*
		마지막 스프라이트 교체 시각이후로 _durationMs만큼의 시간이 지나면
		현재 스프라이트를 다음 스프라이트로 교체한다.
		*/
		void update();

		/*
		현재 스프라이트를 drawPosX, drawPosY에 렌더링한다.
		*/
		void render(HDC hdc, int drawPosX, int drawPosY);

		/*
		누적 데이터를 리셋하고 첫번재 스프라이트부터 재생한다.
		*/
		void restart();

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

		/*
		true로 세팅하면 스프라이트의 좌우가 전환되어 출력된다.
		*/
		inline void enableMirrored(bool enable) {
			_isMirrored = enable;
		}

		/*
		애니메이션 반복 재생 횟수를 설정한다.
		0으로 설정하면 애니메이션을 무한정 반복한다.
		*/
		inline void setMaxReplayCount(int maxReplayCount) {
			_maxReplayCount = maxReplayCount;
		}

		/*
		지금까지 총 애니메이션 반복 횟수를 반환한다.
		restart()메서드를 호출하면 리셋된다.
		*/
		inline int getPlayCount() const {
			return _replayCount;
		}

		/*
		애니메이션에 사용되는 총 스프라이트 개수를 반환한다.
		*/
		inline int getNSprites() const {
			return _sprites.size();
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
		//스프라이트를 좌우 전환하여 그린다
		bool _isMirrored;
	};
}