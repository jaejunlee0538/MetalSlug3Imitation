#pragma once
#include <Windows.h>
#include "SingletonBase.h"
#include <bitset>

#define KEY_MAX 256
namespace SGA {
	class KeyManager : public SGA::SingletonBase<KeyManager>
	{
	private:
		std::bitset<KEY_MAX> _keyUp; //바로 직전의 Key up 여부
		std::bitset<KEY_MAX> _keyDown; //바로 직전의 Key down 여부
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

		//한번만 눌렸을 때
		bool isOnceKeyDown(int key)
		{
			//GetAsyncKeyState ==> 뗀것까지 검사가능
			//GetKeyState ==> 누른것만 검사가능
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

		//한번만 떼었을 때
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

		//계속 누르고 있을 때
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
		////키의 상태가 바뀌었다면 true를 반환(눌림->안눌림, 안눌림->눌림)
		bool isKeyToggled(int key)
		{
			bool current = GetAsyncKeyState(key) & 0x8000;
			bool ret = current != _keyToggle2[key];
			_keyToggle2.set(key, current);
			return ret;
		}


		//딸깍
		bool isToggleKey(int key) {
			//if (isOnceKeyDown(key)) {
			//	_keyToggle[key].flip();
			//}
			//return _keyToggle[key];
			return GetKeyState(key) & 0x0001;//키를 한 번 누를 때 마다 0/1을 왔다 갔다 함.
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