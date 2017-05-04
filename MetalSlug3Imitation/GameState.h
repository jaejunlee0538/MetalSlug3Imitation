#pragma once
namespace SGA {
	class GameState
	{
	public:
		GameState(){}
		virtual ~GameState(){}
		virtual void update();
	};
}