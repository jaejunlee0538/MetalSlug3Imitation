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
		this�� ������ ��ü�� ��ȯ�Ѵ�.
		*/
		SpritesAnimation* clone() const;

		/*
		������ ��������Ʈ ��ü �ð����ķ� _durationMs��ŭ�� �ð��� ������
		���� ��������Ʈ�� ���� ��������Ʈ�� ��ü�Ѵ�.
		*/
		void update();

		/*
		���� ��������Ʈ�� drawPosX, drawPosY�� �������Ѵ�.
		*/
		virtual void render(HDC hdc, int drawPosX, int drawPosY) const;

		/*
		���� �����͸� �����ϰ� ù���� ��������Ʈ���� ����Ѵ�.
		*/
		void restart();

		/*
		�ִϸ��̼ǿ� ����� �ð踦 �����Ѵ�.
		�ʱⰪ : GameWorldClock
		*/
		inline void setClock(const ClockIface* clock) {
			_clock = clock;
		}

		/*
		����� ������ ��������Ʈ�� �ε����� �����Ѵ�.
		*/
		void setCurrentSprite(int spriteIdx);

		/*
		��������Ʈ �ϳ��� ����ð�(millisec)�� �����Ѵ�.
		*/
		inline void setDuration(int durationMillis) {
			_durationMs = durationMillis;
		}

		inline int getDuration() const {
			return _durationMs;
		}

		/*
		�ִϸ��̼� �ݺ� ��� Ƚ���� �����Ѵ�.
		0���� �����ϸ� �ִϸ��̼��� ������ �ݺ��Ѵ�.
		*/
		inline void setMaxReplayCount(int maxReplayCount) {
			_maxReplayCount = maxReplayCount;
		}

		inline int getMaxReplayCount() const{
			return _maxReplayCount;
		}

		/*
		���ݱ��� �� �ִϸ��̼� �ݺ� Ƚ���� ��ȯ�Ѵ�.
		restart()�޼��带 ȣ���ϸ� ���µȴ�.
		*/
		inline int getPlayCount() const {
			return _replayCount;
		}

		/*
		������ Ƚ����ŭ �ִϸ��̼��� �÷��̵Ǹ� true�� ��ȯ.
		_maxReplayCount�� 0�̸� ���ѹݺ��̱� ������ �׻� false�� ��ȯ.
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
		�ִϸ��̼ǿ� ���Ǵ� �� ��������Ʈ ������ ��ȯ�Ѵ�.
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
		//���� ������� ��������Ʈ
		int _currentSprite;
		//�� ��� Ƚ��
		int _replayCount;
		//������ ��������Ʈ�� �ٲ� �ð�
		unsigned long _lastSwitchTime;
		//��������Ʈ ��ȯ �ֱ�
		int _durationMs;
		//��������Ʈ�� �ٽ� ����ϴ� Ƚ��
		int _maxReplayCount;
		//�ִϸ��̼� ����� ����� �ð�
		//default : GameWorldClock
		const ClockIface* _clock;

		bool _active;
	};
}