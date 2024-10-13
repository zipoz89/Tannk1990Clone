#include "GameOverState.h"

#include "Engine.h"
#include "PlayingState.h"
#include "Scene.h"
#include "TankControllerComponent.h"

void GameOverState::Initialize()
{
	std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<TankControllerComponent>();

	for (Entity* tank : Entities)
	{
		TankControllerComponent* tankComponent = tank->GetComponent<TankControllerComponent>();

		if (tankComponent->IsKilled())
		{
			if (tankComponent->GetOwner()->GetName() == "Player1")
			{
				Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate("Player2WinScreen", 0, 0, 1024, 256);
			}
			else
			{
				Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate("Player1WinScreen", 0, 0, 1024, 256);
			}
		}
	}

}

void GameOverState::Update(float DeltaTime)
{
	if (Engine::Get()->GetActiveScene() != nullptr)
	{
		Engine::Get()->GetActiveScene()->Update(DeltaTime);
	}

	m_GameOverTime -= DeltaTime;

	if (m_GameOverTime <= 0)
	{
		Engine::Get()->SetGameState(std::make_unique<PlayingState>());
	}
}

void GameOverState::Uninitialize()
{
	if (Engine::Get()->GetActiveScene() != nullptr)
	{
		Engine::Get()->GetActiveScene()->UnInitialize();
	}
}
