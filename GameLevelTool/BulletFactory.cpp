#include "BulletFactory.h"
#include "Bullet.h"
#include "BulletController.h"
namespace SGA {

	BulletFactory::BulletFactory()
	{

	}

	BulletFactory::~BulletFactory()
	{

	}

	void BulletFactory::init(std::string recipeFile)
	{
	}

	Bullet * BulletFactory::createBullet(std::string bulletName)
	{
		_recipeMap.find(bulletName);
		return nullptr;
	}
}