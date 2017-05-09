#include <json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <SpriteManager.h>
#include <AnimationManager.h>
#include <Global.h>
#include <vector>
#include <CommonUtil.h>
std::string extractSpritePrefix(std::string name) {
	return name.substr(0, name.rfind('_'));
}
int main() {
	std::string spriteFileName = SPRITE_RESOURCE_PATH"SpriteTarma.json";
	std::string aimationFileName = SPRITE_RESOURCE_PATH"AnimationTarma.json";
	std::string aimationOutFileName = "testAnimationOut.json";
	SGA::BitmapImage::setHWND(GetConsoleWindow());
	GET_SPRITE_MANAGER()->loadFromJSON(spriteFileName);
	
	std::ifstream animFile(aimationFileName.c_str());
	if (animFile.good()) {
		animFile.close();
		GET_ANIMATION_MANAGER()->loadFromJSON(aimationFileName);
		//GET_ANIMATION_MANAGER()->saveToJSON(aimationFileName);
	}
	auto &spriteMap = GET_SPRITE_MANAGER()->getSpriteMap();
	std::string spritePrefix;
	std::vector<const SGA::Sprite*> sprites;
	bool skipping = false;
	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		if (skipping) {
			if (spritePrefix != extractSpritePrefix(it->first)) {
				skipping = false;
				spritePrefix = extractSpritePrefix(it->first);
				if (GET_ANIMATION_MANAGER()->hasAnimation(spritePrefix)) {
					skipping = true;
				}
				else {
					skipping = false;
					sprites.push_back(it->second);
				}
			}
		}
		else {
			if (spritePrefix == extractSpritePrefix(it->first)) {
				//스프라이트 모으기
				spritePrefix = extractSpritePrefix(it->first);
				sprites.push_back(it->second);
			}
			else {
				if (!sprites.empty()) {
					//애니메이션 추가
					SGA::SpritesAnimation * animation = new SGA::SpritesAnimation( sprites, 200, 0);
					GET_ANIMATION_MANAGER()->addAnimation(spritePrefix, animation);
					sprites.clear();
				}

				spritePrefix = extractSpritePrefix(it->first);
				if (GET_ANIMATION_MANAGER()->hasAnimation(spritePrefix)) {
					skipping = true;
				}
				else {
					skipping = false;
					sprites.push_back(it->second);
				}
			}
		}
		
	}
	GET_ANIMATION_MANAGER()->saveToJSON(aimationOutFileName);
	GET_SPRITE_MANAGER()->clearAll();
	return 0;
}