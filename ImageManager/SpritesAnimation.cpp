#include "SpritesAnimation.h"
#include "Sprite.h"
#include <WorldClock.h>
#include <assert.h>
#include <algorithm>
SpritesAnimation::SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, int periodMilli, bool replay)
	:_sprites(sprites), _period(periodMilli), _isReplayEnabled(replay)
{
	assert(std::all_of(sprites.begin(), sprites.end(),
		[](const SGA::Sprite* sprite) {return sprite != NULL; }));
	_isFlipped = false;
	restart();
}

SpritesAnimation::~SpritesAnimation()
{
}

void SpritesAnimation::update()
{
	DWORD t = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
	if ((t - _lastSwitchTime) >= _period) {
		_currentSprite++;
		if (_currentSprite == _sprites.size()) {
			if (_isReplayEnabled) {
				//리플레이
				_currentSprite = 0;
				_playCount++;
			}
			else {
				_currentSprite--;
				_playCount = 1;
			}
		}
		_lastSwitchTime = t;
	}
}

void SpritesAnimation::render(HDC hdc, int drawPosX, int drawPosY)
{
	_sprites[_currentSprite]->render(hdc, drawPosX, drawPosY, _isFlipped);
}

void SpritesAnimation::restart()
{
	_currentSprite = 0;
	_playCount = 0;
	_lastSwitchTime = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
}

inline void SpritesAnimation::setCurrentSprite(int spriteIdx) {
	if (spriteIdx >= getNSprites()) {
		spriteIdx = getNSprites() - 1;
	}
	_currentSprite = spriteIdx;
	_lastSwitchTime = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
}
