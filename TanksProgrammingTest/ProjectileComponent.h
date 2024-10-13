#pragma once
#include "ColliderComponent.h"
#include "Sources/Game/PlayerInputComponent.h"

class ProjectileComponent :
    public ColliderComponent
{
public:
    ProjectileComponent(Entity* Owner);
    ProjectileComponent();

    virtual EntityComponent* Clone() const override { return new ProjectileComponent(*this); }

    virtual void LoadFromConfig(nlohmann::json Config) override;
    virtual void Initialize() override;
    virtual void Update(float DeltaTime) override;

    void SetDirection(Direction direction);

private:
    void HandleMovement(float DeltaTime) const;
    void HandleCollision();

    TextureComponent* m_TextureComponent;
    Direction m_Direction;
    float m_Speed;
};

