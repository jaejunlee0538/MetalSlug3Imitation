#pragma once
#include "SingletonBase.h"
#include <string>
#include "GameObject.h"
namespace SGA {
	class GameObjectFactory : public SingletonBase<GameObjectFactory>
	{
	public://TODO : 팩토리에 프로토 타입을 등록하는 식으로 할까 아니면 팩토리에 모든 게임오브젝트를 다 인클루드 할까
		//첫번째 방법으로 하려면 GameObject클래스가 clone을 구현해야한다.
		//두번째 방법은 편하기는 한데 오브젝트가 많아지면 답이 없다.
		GameObjectFactory();
		~GameObjectFactory();
		GameObject* createObject(std::string typeName, std::string tag, int posX, int posY);
	};
}
