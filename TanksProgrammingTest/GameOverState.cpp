#include "GameOverState.h"

#include <iostream>

#include "Engine.h"
#include "PlayingState.h"
#include "Scene.h"
#include "TankControllerComponent.h"

void GameOverState::Initialize()
{
	std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<TankControllerComponent>();

	int killedTanks = 0;

	//check if draw
	for (Entity* tank : Entities)
	{
		TankControllerComponent* tankComponent = tank->GetComponent<TankControllerComponent>();

		if (tankComponent->IsKilled())
		{
			killedTanks++;
		}
	}

	int MaxWidth = 0, MaxHeight = 0;
	SDL_GetWindowSize(Engine::Get()->GetWindow(), &MaxWidth, &MaxHeight);

	if(killedTanks == 2)
	{
		Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate("DrawScreen", MaxWidth / 2 - 512, MaxHeight / 2 - 128, 1024, 256);
	}
	else
	{
		for (Entity* tank : Entities)
		{
			TankControllerComponent* tankComponent = tank->GetComponent<TankControllerComponent>();

			if (tankComponent->IsKilled())
			{
				if (tankComponent->GetOwner()->GetName() == "Player1")
				{
					Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate("Player2WinScreen", MaxWidth / 2 - 512, MaxHeight / 2 - 128, 1024, 256);
				}
				else
				{
					Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate("Player1WinScreen", MaxWidth / 2 - 512, MaxHeight / 2 - 128, 1024, 256);
				}
				break;
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
