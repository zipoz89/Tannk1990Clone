#include "CollideeComponent.h"

#include <iostream>

#include "Engine.h"
#include "Entity.h"
#include "Scene.h"
#include "TextureComponent.h"

CollideeComponent::CollideeComponent(Entity * Owner)
    : ColliderComponent(Owner) {}

CollideeComponent::CollideeComponent()
    : ColliderComponent(nullptr)
{
}

void CollideeComponent::Update(float DeltaTime)
{
    UpdatePoition();

    // Get all entities with ColliderComponents (including other CollideeComponents)
    std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<ColliderComponent>();

    for (Entity* ColliderEntity : Entities)
    {
        // Skip checking against itself
        if (ColliderEntity == GetOwner())
            continue;



        ColliderComponent* Collider = ColliderEntity->GetComponent<ColliderComponent>();
        if (Collider && IsColliding(Collider->GetCollider()))
        {
            HandleCollision(Collider->GetCollider());
        }
    }
}

void CollideeComponent::HandleCollision(const SDL_Rect& ColliderRect)
{
	std::cout << "collision detected" << "\n";
}