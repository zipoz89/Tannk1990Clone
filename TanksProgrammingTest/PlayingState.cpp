#include "PlayingState.h"

#include "Engine.h"
#include "Scene.h"

void PlayingState::Initialize()
{
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
}

void PlayingState::Uninitialize()
{
    //todo
}
