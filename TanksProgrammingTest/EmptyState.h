#pragma once
#include "IState.h"
class EmptyState :
    public IState
{
public:
    void Initialize() override;
    void Update(float DeltaTime) override;
    void Uninitialize() override;
};

