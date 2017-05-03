#pragma once
namespace SGA {
	class Player;
	class PlayerState {
	public:
		virtual ~PlayerState() {}
		virtual void enter(Player& player) = 0;
		virtual void finish(Player& player) = 0;
		virtual PlayerState* update(Player& player) = 0;
	};
}