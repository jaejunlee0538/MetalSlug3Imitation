#include "SpritesAnimation.h"
#include "Sprite.h"
#include <WorldClock.h>
#include <assert.h>
#include <algorithm>
namespace SGA {
	SpritesAnimation::SpritesAnimation(const std::vector<const SGA::Sprite*>& sprites, 
		int durationMilli, int maxReplayCount, bool mirrored)
		:_sprites(sprites), _durationMs(durationMilli), _maxReplayCount(maxReplayCount), _isMirrored(mirrored)
	{
		assert(std::all_of(sprites.begin(), sprites.end(),
			[](const SGA::Sprite* sprite) {return sprite != NULL; }));
		restart();
	}

	SpritesAnimation::~SpritesAnimation()
	{
	}

	void SpritesAnimation::update()
	{
		DWORD t = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
		if (_maxReplayCount != 0 && _replayCount == _maxReplayCount) {
			//���� �ݺ����� �ʰ�, replayCount�� max�� �����ϸ�
			return;
		}
		if ((t - _lastSwitchTime) >= _durationMs) {
			_currentSprite++;
			if (_currentSprite == _sprites.size()) {
				_replayCount++;
				if (_replayCount == _maxReplayCount) {
					//������ ��������Ʈ���� ����� �����.
					_currentSprite -= 1;
				}
				else {
					//�ٽ� ó�� ��������Ʈ���� ���
					_currentSprite = 0;
				}
			}
			_lastSwitchTime = t;
		}
	}

	void SpritesAnimation::render(HDC hdc, int drawPosX, int drawPosY)
	{
		_sprites[_currentSprite]->render(hdc, drawPosX, drawPosY, _isMirrored);
	}

	void SpritesAnimation::restart()
	{
		_currentSprite = 0;
		_replayCount = 0;
		_lastSwitchTime = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
	}

	void SpritesAnimation::setCurrentSprite(int spriteIdx) {
		if (spriteIdx >= getNSprites()) {
			spriteIdx = getNSprites() - 1;
		}
		_currentSprite = spriteIdx;
		_lastSwitchTime = SGA::WorldClock::getSingleton()->getCurrentTimeMillis();
	}
}