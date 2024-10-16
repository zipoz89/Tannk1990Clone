#include "Scene.h"
#include "Entity.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <fstream>
#include <iostream>

void Scene::LoadFromConfig(nlohmann::json Config)
{
	m_Name = Config.value("Name", "");

	if (Config.find("Entities") != Config.end())
	{
		ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
		for (auto Item : Config["Entities"].items())
		{
			Entity* NewEntity = new Entity();

			nlohmann::json EntityConfig = Item.value();
			std::string TypeName = EntityConfig.value("Type", "");
			if (!TypeName.empty())
			{
				nlohmann::json EntityTemplateConfig = ResourceManagerPtr->GetJsonConfig(TypeName, ResourceType::Entity);
				NewEntity->LoadFromConfig(EntityTemplateConfig);
			}
			else
			{
				NewEntity->LoadFromConfig(Item.value());
			}

			AddEntity(NewEntity);
		}
	}

	nlohmann::json::const_iterator SecenLayoutIt = Config.find("SceneLayout");
	if (SecenLayoutIt != Config.end())
	{
		LoadSceneFromLayout((*SecenLayoutIt)["Content"], (*SecenLayoutIt)["Legend"]);
	}
}

void Scene::Initialize()
{
	for (Entity* Entity : m_Entities)
	{
		Entity->Initialize();
	}
}

void Scene::Update(float DeltaTime)
{
	for (Entity* Entity : m_Entities)
	{
		Entity->Update(DeltaTime);
	}

	HandleEntityDestruction();
}



void Scene::Draw()
{
	for (Entity* Entity : m_Entities)
	{
		Entity->Draw();
	}
}

void Scene::UnInitialize()
{
	for (Entity* Entity : m_Entities)
	{
		Entity->UnInitialize();
	}
}

void Scene::AddEntity(Entity* Entity)
{
	m_Entities.push_back(Entity);
}

void Scene::RemoveEntity(Entity* Entity)
{
	auto RetIt = std::remove(m_Entities.begin(), m_Entities.end(), Entity);
}



void Scene::LoadSceneFromLayout(nlohmann::json Content, nlohmann::json Legend)
{
	int Row = 0;
	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	for (auto Item : Content.items())
	{
		int Column = 0;
		const std::string& Line = Item.value();
		for (char Character : Line)
		{
			if (Character != ' ')
			{
				const char Key[] = { Character, '\0' };
				nlohmann::json EntitySpecs = Legend[Key];

				Entity* NewEntity = ResourceManagerPtr->CreateEntityFromDataTemplate(EntitySpecs["Type"]);
				TextureComponent* TextureComponentPtr = NewEntity->GetComponent<TextureComponent>();
				int Width = EntitySpecs["Width"];
				int Height = EntitySpecs["Height"];
				TextureComponentPtr->SetPosition(Column * Width, Row * Height);
				TextureComponentPtr->SetScale(Width, Height);
				AddEntity(NewEntity);
			}
			++Column;
		}
		++Row;
	}
}

Entity* Scene::SpawnEntityFromTemplate(const std::string& TemplateName, int X, int Y, int Width, int Height)
{
	// Get ResourceManager instance
	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();

	// Create the entity using the template from the ResourceManager
	Entity* NewEntity = ResourceManagerPtr->CreateEntityFromDataTemplate(TemplateName);

	// Ensure the entity has a TextureComponent for setting position and scale
	if (NewEntity)
	{
		TextureComponent* TextureComponentPtr = NewEntity->GetComponent<TextureComponent>();
		if (TextureComponentPtr)
		{
			// Set the position and scale of the entity
			TextureComponentPtr->SetPosition(X, Y);
			TextureComponentPtr->SetScale(Width, Height);
		}

		// Add the new entity to the current scene
		AddEntity(NewEntity);

		NewEntity->Initialize();

		return NewEntity;
	}



	return nullptr;
}

void Scene::DestroyEntity(Entity* entity)
{
	m_EntitiesToDestroy.push_back(entity);  // Mark entity for destruction
}

void Scene::HandleEntityDestruction()
{

	// After updating, destroy marked entities
	for (Entity* entityToDestroy : m_EntitiesToDestroy)
	{
		auto it = std::find(m_Entities.begin(), m_Entities.end(), entityToDestroy);
		if (it != m_Entities.end())
		{
			m_Entities.erase(it);  // Remove the entity from the scene
			entityToDestroy->UnInitialize();
			delete entityToDestroy;  // Free memory
		}
	}

	m_EntitiesToDestroy.clear();  // Clear the destruction list after processing
}

PoolableComponent* Scene::GetEntityFromPool(const std::string& type)
{
	auto it = m_PoolManagers.find(type);
	if (it != m_PoolManagers.end())
	{
		return it->second->GetEntity();
	}
	return nullptr;
}

void Scene::ReturnEntityToPool(const std::string& type, PoolableComponent* entity)
{
	auto it = m_PoolManagers.find(type);
	if (it != m_PoolManagers.end())
	{
		it->second->ReturnEntity(entity);
	}
}

void Scene::AddPool(const char* objectTemplate, int initialSize, int textureWidth, int textureHeight)
{
	m_PoolManagers[objectTemplate] = new PoolManager(objectTemplate, initialSize, textureWidth, textureHeight);
}