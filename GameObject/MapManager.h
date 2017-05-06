#pragma once
#include "SingletonBase.h"
#include <string>
#include <vector>
#include "GameObject.h"
#include "ScrollingScene.h"

namespace SGA {
	class MapManager : public SingletonBase<MapManager>
	{
	public:
		MapManager();
		~MapManager();

		void loadFromJSON(std::string fileName, ScrollingScene** farScrollScene, ScrollingScene** closeScrollScene, std::vector<GameObject*>& grounds, std::vector<GameObject*>& gameObjects);
	};

#define GET_MAP_MANAGER()	SGA::MapManager::getSingleton()
}

