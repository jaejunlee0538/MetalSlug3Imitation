#pragma once
#include <Windows.h>
#include "SingletonBase.h"
#include <bitset>

#define KEY_MAX 256
namespace SGA {
	class KeyManager : public SGA::SingletonBase<KeyManager>
	{
	private:
		std::bitset<KEY_MAX> _keyUp; //�ٷ� ������ Key up ����
		std::bitset<KEY_MAX> _keyDown; //�ٷ� ������ Key down ����
		std::bitset<KEY_MAX> _keyToggle; //
		std::bitset<KEY_MAX> _keyToggle2; //
	public:
		KeyManager()
		{
		}

		virtual ~KeyManager()
		{
		}

		//
		HRESULT init(void)
		{
			for (int i = 0; i < KEY_MAX; i++) {
				bool isDown = GetAsyncKeyState(i) & 0x8000;
				_keyUp.set(i, !isDown);
				_keyDown.set(i, isDown);
				_keyToggle.set(i, isDown);
				_keyToggle2.set(i, isDown);
			}
			return S_OK;
		}

		//
		void release(void)
		{

		}

		//�ѹ��� ������ ��
		bool isOnceKeyDown(int key)
		{
			//GetAsyncKeyState ==> ���ͱ��� �˻簡��
			//GetKeyState ==> �����͸� �˻簡��
			if (GetAsyncKeyState(key) & 0x8000) {
				if (!_keyDown[key]) {
					_keyDown.set(key, true);
					return true;
				}
			}
			else {
				_keyDown.set(key, false);
			}
			return false;
		}

		//�ѹ��� ������ ��
		bool isOnceKeyUp(int key)
		{
			if (!(GetAsyncKeyState(key) & 0x8000)) {
				if (!_keyUp[key]) {
					_keyUp.set(key, true);
					return true;
				}
			}
			else {
				_keyUp.set(key, false);
			}
			return false;
		}

		//��� ������ ���� ��
		bool isStayKeyDown(int key)
		{
			if (GetAsyncKeyState(key) & 0x8000) return true;
			return false;
		}

		//
		bool isStayKeyUp(int key)
		{
			if (!(GetAsyncKeyState(key) & 0x8000)) return true;
			return false;
		}

		//
		////Ű�� ���°� �ٲ���ٸ� true�� ��ȯ(����->�ȴ���, �ȴ���->����)
		bool isKeyToggled(int key)
		{
			bool current = GetAsyncKeyState(key) & 0x8000;
			bool ret = current != _keyToggle2[key];
			_keyToggle2.set(key, current);
			return ret;
		}


		//����
		bool isToggleKey(int key) {
			//if (isOnceKeyDown(key)) {
			//	_keyToggle[key].flip();
			//}
			//return _keyToggle[key];
			return GetKeyState(key) & 0x0001;//Ű�� �� �� ���� �� ���� 0/1�� �Դ� ���� ��.
		}

	private:
		bool isKeyUp(int key) const {
			return _keyUp[key];
		}

		bool isKeyDown(int key) const {
			return _keyDown[key];
		}

		void setKeyDown(int key, bool state) {
			_keyDown.set(key, state);
		}

		void setKeyUp(int key, bool state) {
			_keyUp.set(key, state);
		}
	};
#define GET_KEY_MANAGER() SGA::KeyManager::getSingleton()
}