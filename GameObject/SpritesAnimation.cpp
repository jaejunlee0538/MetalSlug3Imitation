#include "SpritesAnimation.h"
#include "Sprite.h"
#include "WorldClock.h"
#include <assert.h>
#include <algorithm>
namespace SGA {
	SpritesAnimation::SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, 
		int durationMilli, int maxReplayCount)
		:_sprites(sprites), _durationMs(durationMilli), _maxReplayCount(maxReplayCount)
	{
		setClock(GET_GAME_WORLD_CLOCK());
		assert(std::all_of(sprites.begin(), sprites.end(),
			[](const SGA::Sprite* sprite) {return sprite != NULL; }));
		_active = false;
		restart();
	}

	SpritesAnimation::~SpritesAnimation()
	{
	}

	SpritesAnimation * SpritesAnimation::clone() const
	{
		SpritesAnimation* newAnimation = new SpritesAnimation(*this);
		newAnimation->restart();
		return newAnimation;
	}

	void SpritesAnimation::update()
	{
		DWORD t = _clock->getCurrentTimeMillis();
		if (_maxReplayCount != 0 && _replayCount == _maxReplayCount) {
			//무한 반복하지 않고, replayCount가 max에 도달하면
			return;
		}
		if ((t - _lastSwitchTime) >= _durationMs) {
			_currentSprite++;
			if (_currentSprite == _sprites.size()) {
				_replayCount++;
				if (_replayCount == _maxReplayCount) {
					//마지막 스프라이트에서 재생을 멈춘다.
					_currentSprite -= 1;
				}
				else {
					//다시 처음 스프라이트부터 재생
					_currentSprite = 0;
				}
			}
			_lastSwitchTime = t;
		}
	}

	void SpritesAnimation::render(HDC hdc, int drawPosX, int drawPosY) const
	{
		_sprites[_currentSprite]->render(hdc, drawPosX, drawPosY);
	}

	void SpritesAnimation::restart()
	{
		_currentSprite = 0;
		_replayCount = 0;
		_lastSwitchTime = _clock->getCurrentTimeMillis();
	}

	void SpritesAnimation::setCurrentSprite(int spriteIdx) {
		if (spriteIdx >= getNSprites()) {
			spriteIdx = getNSprites() - 1;
		}
		_currentSprite = spriteIdx;
		_lastSwitchTime = _clock->getCurrentTimeMillis();
	}
}