#pragma once
#include <vector>
#include <Windows.h>

namespace SGA {
	class Sprite;
}

class SpritesAnimation
{
public:
	SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, int periodMilli, bool replay=true);

	~SpritesAnimation();

	/*
	마지막 스프라이트 교체 시각이후로 _period만큼의 시간이 지나면
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

	inline void enableFlipped(bool enable) {
		_isFlipped = enable;
	}

	/*
	true로 세팅하면 스프라이트 끝에 도달하면 다시 첫번째 스프라이트부터 출력된다.
	*/
	inline void enableReplay(bool enableReplay) {
		_isReplayEnabled = enableReplay;
	}

	/*
	지금까지 총 애니메이션 반복 횟수를 반환한다.
	restart()메서드를 호출하면 리셋된다.
	*/
	inline int getPlayCount() const {
		return _playCount;
	}

	/*
	애니메이션에 사용되는 총 스프라이트 개수를 반환한다.
	*/
	inline int getNSprites() const { 
		return _sprites.size(); 
	}
private:
	std::vector<const SGA::Sprite*> _sprites;
	int _currentSprite;
	int _playCount;
	unsigned long _lastSwitchTime;
	int _period;
	bool _isReplayEnabled;
	bool _isFlipped;
};

