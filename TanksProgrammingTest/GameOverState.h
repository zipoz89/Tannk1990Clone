#pragma once
#include "IState.h"
class GameOverState :
    public IState
{
public:
    void Initialize() override;
    void Update(float DeltaTime) override;
    void Uninitialize() override;

private:
    float m_GameOverTime = 3;
};

