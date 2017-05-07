#pragma once
#include "PlayerStateIface.h"
#include "WorldClock.h"
namespace SGA {
	class PlayerStateStanding :
		public PlayerStateIface
	{
		enum struct Substate {
			TURNING_LEFT,
			TURNING_RIGHT,
			TO_WATCHUP_RIGHT,
			TO_WATCHUP_LEFT,
			THROWING_GRENADE_LEFT,
			THROWING_GRENADE_RIGHT,
			FIRING_LEFT,
			FIRING_RIGHT,
			FIRING_UP_LEFT,
			FIRING_UP_RIGHT,
			KNIFING_LEFT,
			KNIFING_RIGHT,
			FUNMOTION_LEFT,
			FUNMOTION_RIGHT,
			NONE
		};
	public:
		PlayerStateStanding(Player & player);
		virtual ~PlayerStateStanding();

		void update();
		void render();
		void enterState();
		void exitState();
	private:
		void setSubstate(Substate substate);
		void findAnimation();
		void processKeyinput();
		void setAnimation(SpritesAnimation* newAnimation);
		void stateUpdate();
	private:
		int _knifeIdx;
		Substate _subState;
		SpritesAnimation * _currentAnimation;

		SpritesAnimation* _animationTurningRight;
		SpritesAnimation* _animationTurningLeft;

		SpritesAnimation* _animationToWatchingUpRight;
		SpritesAnimation* _animationToWatchingUpLeft;

		SpritesAnimation* _animationWatchingUpRight;
		SpritesAnimation* _animationWatchingUpLeft;

		SpritesAnimation* _animationStandingRight;
		SpritesAnimation* _animationStandingLeft;

		SpritesAnimation* _animationFiringRight;
		SpritesAnimation* _animationFiringLeft;

		SpritesAnimation* _animationFiringUpRight;
		SpritesAnimation* _animationFiringUpLeft;

		SpritesAnimation* _animationKnifingRight[2];
		SpritesAnimation* _animationKnifingLeft[2];

		SpritesAnimation* _animationGrenadeRight;
		SpritesAnimation* _animationGrenadeLeft;

		SpritesAnimation* _animationFunMotionRight[2];
		SpritesAnimation* _animationFunMotionLeft[2];

		TimeoutChecker _funMotionTimeout;
	};
}