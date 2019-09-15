#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

#include "Game\Components\PlayerMovementComponent.h"

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
{
	float boardHeight = 50 * 20;
	float boardWidth = 50 * 20;

	CreatePlayer(25.f, 25.f, 50.f, 50.f);

	CreateObstacle(boardWidth / 2, -1.f, boardWidth, 2.f);
	CreateObstacle(boardWidth / 2, boardHeight, boardWidth, 2.f);
	CreateObstacle(-1.f, boardHeight / 2, 2.f, boardHeight);
	CreateObstacle(boardWidth, boardHeight / 2, 2.f, boardHeight);

	//CreatePlayer(75.f, 75.f, 50.f, 50.f);
	//CreatePlayer(125.f, 125.f, 50.f, 50.f);
}


GameBoard::~GameBoard()
{

}


void GameBoard::CreatePlayer(float xpos, float ypos, float width, float height)
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	
	m_player->SetPos(sf::Vector2f(xpos, ypos));
	m_player->SetSize(sf::Vector2f(width, height));
	
	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
												      (m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Player);

	//Movement
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}


void GameBoard::CreateObstacle(float xpos, float ypos, float width, float height)
{
	GameEngine::Entity* obstacle = new GameEngine::Entity();	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(xpos, ypos));
	obstacle->SetSize(sf::Vector2f(width, height));

	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
		(obstacle->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Obstacle);

	obstacle->AddComponent<GameEngine::CollidableComponent>();
}


void GameBoard::Update()
{	
	
}