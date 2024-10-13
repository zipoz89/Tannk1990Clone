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
{
}

PlayerInputComponent::PlayerInputComponent()
	: PlayerInputComponent(nullptr)
{
}

void PlayerInputComponent::LoadFromConfig(nlohmann::json Config)
{
	ColliderComponent::LoadFromConfig(Config);


	upKey = Config.value("UpKey", SDL_SCANCODE_W);
	downKey = Config.value("DownKey", SDL_SCANCODE_S);
	leftKey = Config.value("LeftKey", SDL_SCANCODE_A);
	rightKey = Config.value("RightKey", SDL_SCANCODE_D);
	shootKey = Config.value("ShootKey", SDL_SCANCODE_SPACE);
}



void addToListIfNotExists(std::list<Direction>& myList, Direction value)
{
	if ((std::find(myList.begin(), myList.end(), value) == myList.end())) 
	{
		myList.push_front(value);
	}
}

void removeFromList(std::list<Direction>& myList, Direction value)
{
	auto it = std::find(myList.begin(), myList.end(), value);
	if (it != myList.end()) 
	{
		myList.erase(it);
	}

}


void PlayerInputComponent::Update(float DeltaTime)
{
	std::vector<SDL_Event> Events = Engine::Get()->GetEvents();

	for (const SDL_Event& Event : Events)
	{
		if(Event.type == SDL_KEYDOWN)
		{
			if (Event.key.keysym.scancode == shootKey)
			{
				isShooting = true;
			}

			if(Event.key.keysym.scancode == upKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, UP);
			}
			if (Event.key.keysym.scancode == downKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, DOWN);
			}
			if (Event.key.keysym.scancode == leftKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, LEFT);
			}
			if (Event.key.keysym.scancode == rightKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, RIGHT);
			}
		}

		if (Event.type == SDL_KEYUP)
		{
			if (Event.key.keysym.scancode == shootKey)
			{
				isShooting = false;
			}

			if (Event.key.keysym.scancode == upKey)
			{
				removeFromList(m_DirectionInputBuffer, UP);
			}
			if (Event.key.keysym.scancode == downKey)
			{
				removeFromList(m_DirectionInputBuffer, DOWN);
			}
			if (Event.key.keysym.scancode == leftKey)
			{
				removeFromList(m_DirectionInputBuffer, LEFT);
			}
			if (Event.key.keysym.scancode == rightKey)
			{
				removeFromList(m_DirectionInputBuffer, RIGHT);
			}
		}

	}

	if (m_DirectionInputBuffer.empty())
	{
		directionInput = Float2(0, 0);
	}
	else
	{
		switch (*m_DirectionInputBuffer.begin())
		{
		case UP:
			directionInput = Float2(0, 1);
			break;
		case DOWN:
			directionInput = Float2(0, -1);
			break;
		case LEFT:
			directionInput = Float2(1, 0);
			break;
		case RIGHT:
			directionInput = Float2(-1, 0);
			break;
		}
	}
}

