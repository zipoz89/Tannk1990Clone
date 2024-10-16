#pragma once
#include "ColliderComponent.h"
#include <vector>

//I used this to create collision system but later decided to add implementation to specific components
class CollideeComponent : public ColliderComponent
{
public:
    CollideeComponent(Entity* Owner);
    CollideeComponent();

    virtual EntityComponent* Clone() const override { return new CollideeComponent(*this); }

    virtual void Update(float DeltaTime) override;
    
private:
    void HandleCollision(const SDL_Rect& ColliderRect);
};