#pragma once
#include "IState.h"

class PlayingState :
    public IState
{
public:
    void Initialize() override;
    void Update(float DeltaTime) override;
    void Uninitialize() override;
private:
    bool m_EndNextFrame = false;
};
