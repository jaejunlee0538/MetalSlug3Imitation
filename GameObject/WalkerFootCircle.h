#pragma once
#include "GameObject.h"
namespace SGA {

class WalkerFootCircle : public GameObject
{
public:
	WalkerFootCircle(int posX, int posY, int radius);

	virtual ~WalkerFootCircle();

	std::string getTag() const {
		return "FootCircle";
	}

	bool isRenderable() const;

	void render();
private:
	int _R;
};
}

