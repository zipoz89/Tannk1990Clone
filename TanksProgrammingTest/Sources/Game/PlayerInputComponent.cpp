#include "PlayerInputComponent.h"

#include <iostream>

#include "TextureComponent.h"
#include "Entity.h"
#include "Engine.h"
#include <algorithm> 
#include "ProjectileComponent.h"
#include "Scene.h"

PlayerInputComponent::PlayerInputComponent(Entity* Owner)
	: ColliderComponent(Owner)
	, m_TextureComponent(nullptr)
{
}

PlayerInputComponent::PlayerInputComponent()
	: PlayerInputComponent(nullptr)
{
}

void PlayerInputComponent::Initialize()
{
	m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
	m_FireCooldown = 0;
	m_FireRate = 1.5;
	m_Speed = 300;
}

void PlayerInputComponent::Update(float DeltaTime)
{
	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();

	SDL_Rect OldPosition = Rectangle;  // Store previous position

	std::vector<SDL_Event> Events = Engine::Get()->GetEvents();

	if(m_FireCooldown > 0)
	{
		m_FireCooldown = std::max(.0f, m_FireCooldown - DeltaTime);
	}

	for (const SDL_Event& Event : Events)
	{
		switch (Event.type)
		{
		case SDL_KEYDOWN:
		{
			switch (Event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				m_CurrentDirection = UP;
				Rectangle.y -= m_Speed * DeltaTime;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				m_CurrentDirection = LEFT;
				Rectangle.x -= m_Speed * DeltaTime;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				m_CurrentDirection = DOWN;
				Rectangle.y += m_Speed * DeltaTime;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				m_CurrentDirection = RIGHT;
				Rectangle.x += m_Speed * DeltaTime;
				break;
			case SDL_SCANCODE_SPACE:
				Shoot();
			default:
				break;
			}
		}
		}
	}

	float Angle = 0;
	switch (m_CurrentDirection)
	{
	case UP:
		Angle = 0;
		break;
	case LEFT:
		Angle = 270;  // 90 degrees counter-clockwise
		break;
	case DOWN:
		Angle = 180;
		break;
	case RIGHT:
		Angle = 90;   // 90 degrees clockwise
		break;
	}

	m_TextureComponent->SetRotation(Angle);

	int MaxWidth = 0, MaxHeight = 0;
	SDL_GetWindowSize(Engine::Get()->GetWindow(), &MaxWidth, &MaxHeight);

	std::vector<Entity*> Entities = Engine::Get()->GetActiveScene()->GetEntitiesWithComponent<ColliderComponent>();

	for (Entity* ColliderEntity : Entities)
	{
		if (ColliderEntity == GetOwner())
			continue;

		ColliderComponent* Collider = ColliderEntity->GetComponent<ColliderComponent>();
		if (Collider && Collider->IsColliding(Rectangle))
		{
			std::cout << "collision detected" << "\n";
			Rectangle = OldPosition;
		}
	}


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

void PlayerInputComponent::Shoot()
{
	if(m_FireCooldown > 0)
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
