#include "PlayerInputComponent.h"

#include <iostream>

#include "TextureComponent.h"
#include "Entity.h"
#include "Engine.h"
#include <algorithm> 
#include "ProjectileComponent.h"
#include "Scene.h"

PlayerInputComponent::PlayerInputComponent(Entity* Owner)
	: EntityComponent(Owner)
{
}

PlayerInputComponent::PlayerInputComponent()
	: PlayerInputComponent(nullptr)
{
}

void PlayerInputComponent::LoadFromConfig(nlohmann::json Config)
{
	EntityComponent::LoadFromConfig(Config);


	m_UpKey = Config.value("UpKey", SDL_SCANCODE_W);
	m_DownKey = Config.value("DownKey", SDL_SCANCODE_S);
	m_LeftKey = Config.value("LeftKey", SDL_SCANCODE_A);
	m_RightKey = Config.value("RightKey", SDL_SCANCODE_D);
	m_ShootKey = Config.value("ShootKey", SDL_SCANCODE_SPACE);
}


//I'm sure there is a way to do it in O(1) but I couldn't find any suitable collection type
//I'm mainly programmed in c# where I would use hash set, but it seems that in c++ set and unordered set doesn't hold the order of insertion
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

//the input is collected and stored in buffer so that if you stop holding one button it falls back to last pressed one
void PlayerInputComponent::Update(float DeltaTime)
{
	std::vector<SDL_Event> Events = Engine::Get()->GetEvents();

	for (const SDL_Event& Event : Events)
	{
		if(Event.type == SDL_KEYDOWN)
		{
			if (Event.key.keysym.scancode == m_ShootKey)
			{
				m_IsShooting = true;
			}

			if(Event.key.keysym.scancode == m_UpKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, UP);
			}
			if (Event.key.keysym.scancode == m_DownKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, DOWN);
			}
			if (Event.key.keysym.scancode == m_LeftKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, LEFT);
			}
			if (Event.key.keysym.scancode == m_RightKey)
			{
				addToListIfNotExists(m_DirectionInputBuffer, RIGHT);
			}
		}

		if (Event.type == SDL_KEYUP)
		{
			if (Event.key.keysym.scancode == m_ShootKey)
			{
				m_IsShooting = false;
			}

			if (Event.key.keysym.scancode == m_UpKey)
			{
				removeFromList(m_DirectionInputBuffer, UP);
			}
			if (Event.key.keysym.scancode == m_DownKey)
			{
				removeFromList(m_DirectionInputBuffer, DOWN);
			}
			if (Event.key.keysym.scancode == m_LeftKey)
			{
				removeFromList(m_DirectionInputBuffer, LEFT);
			}
			if (Event.key.keysym.scancode == m_RightKey)
			{
				removeFromList(m_DirectionInputBuffer, RIGHT);
			}
		}

	}

	if (m_DirectionInputBuffer.empty())
	{
		m_DirectionInput = Float2(0, 0);
	}
	else
	{
		switch (*m_DirectionInputBuffer.begin())
		{
		case UP:
			m_DirectionInput = Float2(0, 1);
			break;
		case DOWN:
			m_DirectionInput = Float2(0, -1);
			break;
		case LEFT:
			m_DirectionInput = Float2(1, 0);
			break;
		case RIGHT:
			m_DirectionInput = Float2(-1, 0);
			break;
		}
	}
}

