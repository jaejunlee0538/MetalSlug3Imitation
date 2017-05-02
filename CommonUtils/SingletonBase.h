#pragma once
namespace SGA {
	/*
	넓은 범위에서 자주 사용하는 객체 또는 프로그램 내에서 오직 하나만 존재해야 하는 객체를
	싱글톤으로 만든다.
	*/
	template <typename T>
	class SingletonBase
	{
	public:
		//인스턴스 가져온다
		static T* getSingleton();
		//인스턴스 해제
		void releaseSingleton();
	protected:
		SingletonBase() {}
		virtual ~SingletonBase() {}
		static T* _singleTon;
	};

	template <typename T>
	T* SingletonBase<T>::getSingleton() {
		if (!_singleTon) {
			_singleTon = new T();
		}
		return _singleTon;
	}

	template <typename T>
	void SingletonBase<T>::releaseSingleton() {
		if (_singleTon) {
			delete _singleTon;
		}
		_singleTon = nullptr;
	}

	template <typename T>
	T* SingletonBase<T>::_singleTon = nullptr;
}