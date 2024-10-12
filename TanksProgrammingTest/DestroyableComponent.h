#pragma once
#include "EntityComponent.h"

class DestroyableComponent : public EntityComponent
{
public:
    DestroyableComponent(Entity* Owner) : EntityComponent(Owner) {}
    DestroyableComponent() : EntityComponent(nullptr) {}

    virtual EntityComponent* Clone() const override { return new DestroyableComponent(*this); }

    virtual void Initialize() override {}
    virtual void Update(float DeltaTime) override {}
};