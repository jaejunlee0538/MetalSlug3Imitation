#pragma once
namespace SGA {
	/*
	���� �������� ���� ����ϴ� ��ü �Ǵ� ���α׷� ������ ���� �ϳ��� �����ؾ� �ϴ� ��ü��
	�̱������� �����.
	*/
	template <typename T>
	class SingletonBase
	{
	public:
		//�ν��Ͻ� �����´�
		static T* getSingleton();
		//�ν��Ͻ� ����
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