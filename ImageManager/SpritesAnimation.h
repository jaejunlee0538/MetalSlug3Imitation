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
	������ ��������Ʈ ��ü �ð����ķ� _period��ŭ�� �ð��� ������
	���� ��������Ʈ�� ���� ��������Ʈ�� ��ü�Ѵ�.
	*/
	void update();

	/*
	���� ��������Ʈ�� drawPosX, drawPosY�� �������Ѵ�.
	*/
	void render(HDC hdc, int drawPosX, int drawPosY);

	/*
	���� �����͸� �����ϰ� ù���� ��������Ʈ���� ����Ѵ�.
	*/
	void restart();

	/*
	����� ������ ��������Ʈ�� �ε����� �����Ѵ�.
	*/
	void setCurrentSprite(int spriteIdx);

	inline void enableFlipped(bool enable) {
		_isFlipped = enable;
	}

	/*
	true�� �����ϸ� ��������Ʈ ���� �����ϸ� �ٽ� ù��° ��������Ʈ���� ��µȴ�.
	*/
	inline void enableReplay(bool enableReplay) {
		_isReplayEnabled = enableReplay;
	}

	/*
	���ݱ��� �� �ִϸ��̼� �ݺ� Ƚ���� ��ȯ�Ѵ�.
	restart()�޼��带 ȣ���ϸ� ���µȴ�.
	*/
	inline int getPlayCount() const {
		return _playCount;
	}

	/*
	�ִϸ��̼ǿ� ���Ǵ� �� ��������Ʈ ������ ��ȯ�Ѵ�.
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

