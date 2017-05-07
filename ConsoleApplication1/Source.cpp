#include <list>
#include <iostream>
#include <string>
class MYClass {
public:
	void addChild(MYClass* child) {
		_child.push_back(child);
	}

	void print(int depth = 0) {
		std::cout << std::string(depth, ' ') << _hitCount << std::endl;
		for (auto it = _child.begin(); it != _child.end(); ++it) {
			(*it)->print(depth+1);
		}
	}

	//other와 other의 자식들을 만난다.
	//aaa가 true면 other와 other의 자식들을 소개 받는다.
	//aaa가 false면 
	void collisionCheck(MYClass* other) {
		collisionCheckInternal(other, true);
	}

private:
	//other와 other의 자식들을 만난다.
	//aaa가 true면 other와 other의 자식들을 소개 받는다.
	//aaa가 false면 
	void collisionCheckInternal(MYClass* other, bool aaa) {
		if (aaa) {
			other->collisionCheckInternal(this, false);
			for (auto it = _child.begin(); it != _child.end(); ++it) {
				other->collisionCheckInternal(*it, true);
			}
		}
		else {
			other->_hitCount++;
			_hitCount++;

			for (auto it = _child.begin(); it != _child.end(); ++it) {
				(*it)->collisionCheckInternal(other, false);
			}
		}
	}

	std::list<MYClass*> _child;
	int _hitCount = 0;
};
bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.rfind(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
int main() {
	std::string name = "Tarma_RightNormal_Pistol_IDLE_Right_0";
	replace(name, "Right", "Left");
	std::cout << name << std::endl;
	//MYClass myClass[500];
	//myClass[0].addChild(&myClass[1]);
	//myClass[0].addChild(&myClass[2]);
	//myClass[0].addChild(&myClass[3]);
	//myClass[2].addChild(&myClass[20]);
	//myClass[2].addChild(&myClass[21]);
	//myClass[20].addChild(&myClass[200]);
	//myClass[20].addChild(&myClass[201]);

	//MYClass myClass2[500];
	//myClass2[0].addChild(&myClass2[1]);
	//myClass2[0].addChild(&myClass2[2]);
	//myClass2[0].addChild(&myClass2[3]);
	//myClass2[2].addChild(&myClass2[20]);
	//myClass2[2].addChild(&myClass2[21]);
	//myClass2[20].addChild(&myClass2[200]);
	//myClass2[20].addChild(&myClass2[201]);

	//myClass[0].collisionCheck(&myClass2[0]);
	//
	//myClass[0].print();

	//myClass2[0].print();

	return 0;
}