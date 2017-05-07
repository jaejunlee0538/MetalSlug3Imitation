#pragma once
#include "SingletonBase.h"
#include <string>
#include "GameObject.h"
namespace SGA {
	class GameObjectFactory : public SingletonBase<GameObjectFactory>
	{
	public://TODO : ���丮�� ������ Ÿ���� ����ϴ� ������ �ұ� �ƴϸ� ���丮�� ��� ���ӿ�����Ʈ�� �� ��Ŭ��� �ұ�
		//ù��° ������� �Ϸ��� GameObjectŬ������ clone�� �����ؾ��Ѵ�.
		//�ι�° ����� ���ϱ�� �ѵ� ������Ʈ�� �������� ���� ����.
		GameObjectFactory();
		~GameObjectFactory();
		GameObject* createObject(std::string typeName, std::string tag, int posX, int posY);
	};
}
