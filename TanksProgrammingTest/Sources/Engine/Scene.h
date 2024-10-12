#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "PoolManager.h"
#include "Entity.h"



class Scene
{

public:
	void LoadFromConfig(nlohmann::json Config);
	void Initialize();
	void Update(float DeltaTime);
	void Draw();
	void UnInitialize();

	void AddEntity(Entity* Entity);
	void RemoveEntity(Entity* Entity);

	PoolableComponent* GetEntityFromPool(const std::string& type);
	void ReturnEntityToPool(const std::string& type, PoolableComponent* entity);
	void AddPool(const char* objectTemplate, int initialSize);

	template<typename T>
    std::vector<Entity*> GetEntitiesWithComponent() {
        std::vector<Entity*> entitiesWithComponent;
        for (Entity* entity : m_Entities) {
            if (entity->GetComponent<T>() != nullptr) {
                entitiesWithComponent.push_back(entity);
            }
        }
        return entitiesWithComponent;
    }




	Entity* SpawnEntityFromTemplate(const std::string& TemplateName, int X, int Y, int Width, int Height);
	void DestroyEntity(Entity* entity);
	

private:
	void LoadSceneFromLayout(nlohmann::json Content, nlohmann::json Legend);
	void HandleEntityDestruction();
	std::list<Entity*> m_Entities;
	std::string m_Name;
	std::vector<Entity*> m_EntitiesToDestroy;
    std::map<std::string, PoolManager*> m_PoolManagers;
};
