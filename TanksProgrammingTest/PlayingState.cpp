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

    Engine::Get()->CreateActiveSceneFromTemplate("MainScene");
    Engine::Get()->GetActiveScene()->AddPool("Projectile", 10, 10, 10);

    if (Engine::Get()->GetActiveScene() != nullptr)
    {
        Engine::Get()->GetActiveScene()->Initialize();
    }

}
//I check for the killed players here, ideally I would use some external manager with teams
void PlayingState::Update(float DeltaTime)
{
    if (Engine::Get()->GetActiveScene() != nullptr)
    {
        Engine::Get()->GetActiveScene()->Update(DeltaTime);
    }

    if(m_EndNextFrame)
    {
        Engine::Get()->SetGameState(std::make_unique<GameOverState>());
    }

    std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<TankControllerComponent>();


    for (Entity* tank : Entities)
    {
        TankControllerComponent* tankComponent = tank->GetComponent<TankControllerComponent>();

        if(tankComponent->IsKilled())
        {
            m_EndNextFrame = true;
            break;
        }
    }
}

void PlayingState::Uninitialize()
{
}
