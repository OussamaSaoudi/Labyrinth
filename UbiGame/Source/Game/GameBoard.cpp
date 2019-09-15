#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

#include "Game\Components\PlayerMovementComponent.h"
#include "Game\Entities\ObstacleEntity.h"
#include "Game\Entities\NumberEntity.h"


using namespace Game;


GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
{
	CreateBackGround();
	for (int i = 0; i < 20; ++i)
		tiles[i] = new int[20];

	for (int a = 0; a < 20; ++a) //This is the initilizer, you have this for loop to create whatever you want to start. 
	{
		for (int b = 0; b < 20; ++b) {
			tiles[a][b] = 0;
		}

	}
	tiles[2][2] = 2;
	tiles[3][3] = 3;
	tiles[4][4] = 4;
	tiles[5][5] = 5;
	MakeGrid();

	
	float boardHeight = 50 * 20;
	float boardWidth = 50 * 20;

	CreatePlayer(25.f, 25.f, 50.f, 50.f);

	CreateObstacle(boardWidth / 2, -1.f, boardWidth, 2.f);
	CreateObstacle(boardWidth / 2, boardHeight, boardWidth, 2.f);
	CreateObstacle(-1.f, boardHeight / 2, 2.f, boardHeight);
	CreateObstacle(boardWidth, boardHeight / 2, 2.f, boardHeight);


	

	
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
	spriteRender->SetZLevel(5);

	//Movement
	PlayerMovementComponent* movement = static_cast<PlayerMovementComponent*>(m_player->AddComponent<PlayerMovementComponent>());
	movement->SetBoard(this);

	m_player->AddComponent<GameEngine::AnimationComponent>();

	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}


void GameBoard::CreateObstacle(float xpos, float ypos, float width, float height) // Everything to do with the block. Use as example. Also, must be put above in GameBoard
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

void GameBoard::CreateBackGround() //copied from flappy bird code. 
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity(); //Create new entity, must be done for everything
	//render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::BG); //Background image in ManageTexture
	render->SetZLevel(0);//should push it to back, really don't work
	bgEntity->SetPos(sf::Vector2f(250.f, 250.f));//position should be the mid point
	bgEntity->SetSize(sf::Vector2f(500.f, 500.f));//Size should be size of frame
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity); //NO FUCKING IDEA

	m_backGround = bgEntity;
}

void GameBoard::PlayerUpdate(const int xCor,const int yCor) //Changing 2D array to track objects. 
{
	const int a = (xCor - 25) / 50;
	const int b = (yCor - 25) / 50;

	if (tiles[a][b] == -1) //LOSER
	{
		
	}
	else if (tiles[a][b]<-1 && tiles[a][b]!=-6)
	{
		tiles[a][b] = -tiles[a][b];
	}
	else if (tiles[a][b] == 0)
	{
		
		OpenSpace(a, b);
	}
	else if (tiles[a][b]==-6) { //WINNER

	}
	DeleteBlock();
	MakeGrid();

}

void GameBoard::OpenSpace(const int a, const int b) {
tiles[a][b] = 1;

if (a != 19)
OpenSpace(a + 1, b);
if (a != 0)
OpenSpace(a - 1, b);
if (b != 19)
OpenSpace(a, b+ 1);
if (b != 0)
OpenSpace(a, b-1);

}

void GameBoard::DeleteBlock() { //Delete all the blocks to then be put back on the grid

for (std::vector<GameEngine::Entity*>::iterator it = m_blocks.begin(); it != m_blocks.end();)
		{
			GameEngine::Entity* obstacle = (*it);
			sf::Vector2f currPos = obstacle->GetPos();
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			it = m_blocks.erase(it);
		}

}

void GameBoard::MakeGrid()
{
	int xTiles = 20;
	int yTiles = 20;
	int TileSize = 50;

	for (int a = 0; a < xTiles; a++)
	{
		for (int b = 0; b < yTiles; b++) {
			
			sf::Vector2f pos = sf::Vector2f(a * 50.f + 25.f, b * 50.f + 25.f);
			sf::Vector2f size = sf::Vector2f(50.f, 50.f);

		if (tiles[a][b] == 0) {
			CreateDark(pos, size);
		}
		else if (tiles[a][b] > 1) {
			CreateNumTiles(pos, size, tiles[a][b]);
		}
		
		}
	}
}


void GameBoard::CreateDark(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* block = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(block);

	block->SetPos(pos);
	block->SetSize(sf::Vector2f(size.x, size.y));

	m_blocks.push_back(block);
	
}

void GameBoard::CreateNumTiles(const sf::Vector2f& pos, const sf::Vector2f& size,const int num) 
{
	NumberEntity* Tile = new NumberEntity(num);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(Tile);

	Tile->SetPos(pos);
	Tile->SetSize(sf::Vector2f(size.x, size.y));

	m_blocks.push_back(Tile);

}

/*
void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}
*/


void GameBoard::Update()
{	
	
}