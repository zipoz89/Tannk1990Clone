#include "ProjectileComponent.h"

#include <iostream>

#include "ColliderComponent.h"
#include "DestroyableComponent.h"
#include "Entity.h"
#include "Engine.h"
#include "Scene.h"
#include "TextureComponent.h"

ProjectileComponent::ProjectileComponent(Entity* Owner)
    : ColliderComponent(Owner)
    , m_Speed(400.0f)  // Default speed
    , m_TextureComponent(nullptr)
{
}

ProjectileComponent::ProjectileComponent()
    : ProjectileComponent(nullptr)
{
}

void ProjectileComponent::Initialize()
{
    m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
}




void ProjectileComponent::Update(float DeltaTime)
{
    if(!GetOwner()->GetComponent<PoolableComponent>()->IsActive())
    {
        return;
    }

    HandleMovement(DeltaTime);
    HandleCollision();
}

void ProjectileComponent::HandleMovement(float DeltaTime) const
{
	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();

	switch (m_Direction) {
	case UP:
		Rectangle.y -= m_Speed * DeltaTime;
		break;
	case DOWN:
		Rectangle.y += m_Speed * DeltaTime;
		break;
	case LEFT:
		Rectangle.x -= m_Speed * DeltaTime;
		break;
	case RIGHT:
		Rectangle.x += m_Speed * DeltaTime;
		break;
	}
}

void ProjectileComponent::HandleCollision()
{
	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();

	std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<ColliderComponent>();

	for (Entity* ColliderEntity : Entities) {
		if (ColliderEntity == GetOwner())
			continue;

		ColliderComponent* Collider = ColliderEntity->GetComponent<ColliderComponent>();


		if (Collider && Collider->IsColliding(Rectangle)) 
		{

			if (DestroyableComponent* destroyableComponent = ColliderEntity->GetComponent<DestroyableComponent>()) {
				destroyableComponent->Destroy();
				
			}

			if (TankControllerComponent* tankControllerComponent = ColliderEntity->GetComponent<TankControllerComponent>())
			{
				tankControllerComponent->Kill();
			}

			Engine::Get()->GetActiveScene()->ReturnEntityToPool("Projectile", GetOwner()->GetComponent<PoolableComponent>());
			break;
		}
	}

	int MaxWidth = 0, MaxHeight = 0;
	SDL_GetWindowSize(Engine::Get()->GetWindow(), &MaxWidth, &MaxHeight);


	if (Rectangle.x + Rectangle.w > MaxWidth ||
		Rectangle.x < 0 ||
		Rectangle.y + Rectangle.h > MaxHeight ||
		Rectangle.y < 0)
	{
		Engine::Get()->GetActiveScene()->ReturnEntityToPool("Projectile", GetOwner()->GetComponent<PoolableComponent>());

	}
}

void ProjectileComponent::SetDirection(Direction direction)
{
    m_Direction = direction;
}

void ProjectileComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}
