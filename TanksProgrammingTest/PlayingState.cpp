#include "PlayingState.h"

#include <iostream>

#include "Engine.h"
#include "GameOverState.h"
#include "Scene.h"
#include "TankControllerComponent.h"

void PlayingState::Initialize()
{
    if (Engine::Get()->GetActiveScene() != nullptr)
    {
        Engine::Get()->GetActiveScene()->UnInitialize();
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    Engine::Get()->CreateActiveSceneFromTemplate("MainScene");
    Engine::Get()->GetActiveScene()->AddPool("Projectile", 10, 10, 10);

    if (Engine::Get()->GetActiveScene() != nullptr)
    {
        Engine::Get()->GetActiveScene()->Initialize();
    }
}

void PlayingState::Update(float DeltaTime)
{
    if (Engine::Get()->GetActiveScene() != nullptr)
    {
        Engine::Get()->GetActiveScene()->Update(DeltaTime);
    }

    std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<TankControllerComponent>();


    for (Entity* tank : Entities)
    {
        TankControllerComponent* tankComponent = tank->GetComponent<TankControllerComponent>();

        if(tankComponent->IsKilled())
        {
            Engine::Get()->SetGameState(std::make_unique<GameOverState>());
        }
    }
}

void PlayingState::Uninitialize()
{
    //todo
}
