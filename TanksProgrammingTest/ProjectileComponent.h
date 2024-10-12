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

    virtual void Initialize() override;
    void HandleMovement(float DeltaTime) const;
    void HandleCollision();
    virtual void Update(float DeltaTime) override;

    void SetDirection(Direction direction);
    void SetSpeed(float speed);
    //void Destroy();

private:
    Direction m_Direction;
    float m_Speed;
    TextureComponent* m_TextureComponent;

};

