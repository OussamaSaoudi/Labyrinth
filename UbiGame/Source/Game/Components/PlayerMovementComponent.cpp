#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"

#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
	: m_lastFaceIndex(0)
	, m_wasFaceSwapButtonPressed(false)
	, m_wasRightPressed(false)
	, m_wasLeftPressed(false)
	, m_wasUpPressed(false)
	, m_wasDownPressed(false)
	, m_numSteps(0)
{

}


PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void PlayerMovementComponent::Update()
{
	__super::Update();

	//Grabs how much time has passed since the last Update() call
	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	//by default the wanted velocity is 0
	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);
	//player Velocity is applied when we have some input (for the time being let's make it 10pixels a second)
	float playerVel = 100.f;

	int maxNumSteps = 100;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_numSteps == 0)
	{
		m_wasLeftPressed = true;
	}
	else
	{
		if (m_wasLeftPressed) 
		{
			wantedVel.x -= .5;
			m_numSteps += 1;
		}
		if (m_numSteps == maxNumSteps)
		{
			m_wasLeftPressed = false;
			m_numSteps = 0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_wasRightPressed = true;
	}
	else
	{
		if (m_wasRightPressed)
		{
			wantedVel.x += 50;//playerVel * dt;
		}
		m_wasRightPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_wasUpPressed = true;
	}
	else
	{
		if (m_wasUpPressed)
		{
			wantedVel.y -= 50;//playerVel * dt;
		}
		m_wasUpPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_wasDownPressed = true;
	}
	else
	{
		if (m_wasDownPressed)
		{
			wantedVel.y += 50;//playerVel * dt;
		}
		m_wasDownPressed = false;
	}

	int maxFaces = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_wasFaceSwapButtonPressed = true;
	}
	else
	{
		//Button is not pressed now, but it was pressed last frame, which means it just has been released
		if (m_wasFaceSwapButtonPressed)
		{
			GameEngine::AnimationComponent* animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
			if (animComponent)
			{
				//animComponent->SetIsLooping(false);
				animComponent->PlayAnim(GameEngine::EAnimationId::PlayerWink);
			}
		}

		m_wasFaceSwapButtonPressed = false;
	}

	
	//Update the entity position with new velocity
	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);	
}