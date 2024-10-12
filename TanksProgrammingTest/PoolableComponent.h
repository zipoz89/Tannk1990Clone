#pragma once
#include "EntityComponent.h"

class PoolableComponent : public EntityComponent
{
public:
    PoolableComponent(Entity* Owner) : EntityComponent(Owner) { m_IsActive = false; }
    PoolableComponent() : EntityComponent(nullptr) { m_IsActive = false; }

    virtual EntityComponent* Clone() const override { return new PoolableComponent(*this); }

    bool IsActive() const { return m_IsActive; }
    void OnReturnedToPool() { m_IsActive = false; }
    void OnGetToPool() { m_IsActive = true; }

protected:
    bool m_IsActive;
};

