#include "TankControllerComponent.h"

#include <iostream>

#include "Engine.h"
#include "Entity.h"
#include "ProjectileComponent.h"
#include "Scene.h"
#include "TextureComponent.h"

class ProjectileComponent;

TankControllerComponent::TankControllerComponent(Entity* Owner)
	: ColliderComponent(Owner)
	, m_TextureComponent(nullptr)
	, m_Destroyed(false)
{
}

TankControllerComponent::TankControllerComponent()
	: TankControllerComponent(nullptr)
{
}

void TankControllerComponent::Initialize()
{
	m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
	m_PlayerInputComponent = GetOwner()->GetComponent<PlayerInputComponent>();
	m_FireCooldown = 0;
	m_FireRate = 1.5;
	m_Speed = 300;
}

void TankControllerComponent::UnInitialize()
{
	
}

void TankControllerComponent::Update(float DeltaTime)
{
	HandleMovement(DeltaTime);
	HandleShooting(DeltaTime);
}


//the movement is limited to one direction so
void TankControllerComponent::HandleMovement(float DeltaTime)
{
	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();

	SDL_Rect OldPosition = Rectangle;  // Store previous position


	Float2 moveDirection = m_PlayerInputComponent->GetDirection();

	Rectangle.y -= m_Speed * DeltaTime * moveDirection.y;
	Rectangle.x -= m_Speed * DeltaTime * moveDirection.x;

	float Angle = 0;

	if(moveDirection.y < 0)
	{
		m_CurrentDirection = DOWN;
	}
	else if(moveDirection.y > 0)
	{
		m_CurrentDirection = UP;
	}
	else if (moveDirection.x < 0)
	{
		m_CurrentDirection = RIGHT;
	}
	else if (moveDirection.x > 0)
	{
		m_CurrentDirection = LEFT;
	}

	switch (m_CurrentDirection)
	{
	case UP:
		Angle = 0;
		break;
	case LEFT:
		Angle = 270;
		break;
	case DOWN:
		Angle = 180;
		break;
	case RIGHT:
		Angle = 90;
		break;
	}

	m_TextureComponent->SetRotation(Angle);


	std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<ColliderComponent>();

	for (Entity* ColliderEntity : Entities)
	{
		if (ColliderEntity == GetOwner())
			continue;

		ColliderComponent* Collider = ColliderEntity->GetComponent<ColliderComponent>();
		if (Collider && Collider->IsColliding(Rectangle))
		{
			Rectangle = OldPosition;
		}
	}

	int MaxWidth = 0, MaxHeight = 0;
	SDL_GetWindowSize(Engine::Get()->GetWindow(), &MaxWidth, &MaxHeight);


	if (Rectangle.x + Rectangle.w > MaxWidth)
	{
		Rectangle.x = MaxWidth - Rectangle.w;

	}

	if (Rectangle.x < 0)
	{
		Rectangle.x = 0;
	}

	if (Rectangle.y + Rectangle.h > MaxHeight)
	{
		Rectangle.y = MaxHeight - Rectangle.h;
	}

	if (Rectangle.y < 0)
	{
		Rectangle.y = 0;
	}
}


void TankControllerComponent::HandleShooting(float DeltaTime)
{
	if (m_FireCooldown > 0)
	{
		m_FireCooldown = std::max(.0f, m_FireCooldown - DeltaTime);
	}

	if (m_PlayerInputComponent->GetShooting())
	{
		Shoot();
	}
}

void TankControllerComponent::Shoot()
{
	if (m_FireCooldown > 0)
	{
		return;
	}

	m_FireCooldown = 1 / m_FireRate;


	Entity* projectile = Engine::Get()->GetActiveScene()->GetEntityFromPool("Projectile")->GetOwner();
	ProjectileComponent* projComp = projectile->GetComponent<ProjectileComponent>();

	TextureComponent* TextureComponentPtr = projectile->GetComponent<TextureComponent>();


	SDL_Rect tankRect = m_TextureComponent->GetRectangle();

	// Set the projectile's position and direction based on tank's current direction
	switch (m_CurrentDirection) {
	case UP:
		projComp->SetDirection(UP);
		TextureComponentPtr->SetPosition(tankRect.x + tankRect.w / 2, tankRect.y - 10);
		break;
	case DOWN:
		projComp->SetDirection(DOWN);
		TextureComponentPtr->SetPosition(tankRect.x + tankRect.w / 2, tankRect.y + tankRect.h + 10);
		break;
	case LEFT:
		projComp->SetDirection(LEFT);
		TextureComponentPtr->SetPosition(tankRect.x - 10, tankRect.y + tankRect.h / 2);
		break;
	case RIGHT:
		projComp->SetDirection(RIGHT);
		TextureComponentPtr->SetPosition(tankRect.x + tankRect.w + 10, tankRect.y + tankRect.h / 2);
		break;
	}

	projComp->SetSpeed(600.0f);

}
