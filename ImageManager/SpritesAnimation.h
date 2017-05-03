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
		������ ��������Ʈ ��ü �ð����ķ� _durationMs��ŭ�� �ð��� ������
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

		/*
		��������Ʈ �ϳ��� ����ð�(millisec)�� �����Ѵ�.
		*/
		inline void setDuration(int durationMillis) {
			_durationMs = durationMillis;
		}

		/*
		true�� �����ϸ� ��������Ʈ�� �¿찡 ��ȯ�Ǿ� ��µȴ�.
		*/
		inline void enableMirrored(bool enable) {
			_isMirrored = enable;
		}

		/*
		�ִϸ��̼� �ݺ� ��� Ƚ���� �����Ѵ�.
		0���� �����ϸ� �ִϸ��̼��� ������ �ݺ��Ѵ�.
		*/
		inline void setMaxReplayCount(int maxReplayCount) {
			_maxReplayCount = maxReplayCount;
		}

		/*
		���ݱ��� �� �ִϸ��̼� �ݺ� Ƚ���� ��ȯ�Ѵ�.
		restart()�޼��带 ȣ���ϸ� ���µȴ�.
		*/
		inline int getPlayCount() const {
			return _replayCount;
		}

		/*
		�ִϸ��̼ǿ� ���Ǵ� �� ��������Ʈ ������ ��ȯ�Ѵ�.
		*/
		inline int getNSprites() const {
			return _sprites.size();
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
		//��������Ʈ�� �¿� ��ȯ�Ͽ� �׸���
		bool _isMirrored;
	};
}