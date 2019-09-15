#pragma once
#include "GameEngine\EntitySystem\Component.h"

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

		void CheckBedVisit();

	private:
		bool m_wasFaceSwapButtonPressed;
		bool m_wasRightPressed;
		bool m_wasLeftPressed;
		bool m_wasUpPressed;
		bool m_wasDownPressed;
		int m_numSteps;
		float m_x;
		float m_y;
	};
}