#pragma once
#include <SingletonBase.h>
#include <string>
#include <unordered_map>
namespace SGA {
	class Bullet;
	class BulletCtrlIface;
	class BulletFactory:public SingletonBase<BulletFactory>
	{
		typedef std::unordered_map<std::string, Bullet*> BulletRecipeMap;
	public:
		BulletFactory();
		~BulletFactory();
		void init(std::string recipeFile);
		Bullet* createBullet(std::string bulletName);
	private:
		BulletRecipeMap _recipeMap;
	};
}