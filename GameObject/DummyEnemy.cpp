#include "DummyEnemy.h"

namespace SGA {

	DummyEnemy::DummyEnemy()
		:Enemy("Dummy", 100, 30, 80,100)
	{
		setActive();
	}


	DummyEnemy::~DummyEnemy()
	{
	}

	void DummyEnemy::render()
	{
		_renderLayer->drawRectangleInWorld(getPosition().x, getPosition().y, 30, 80);
	}
}