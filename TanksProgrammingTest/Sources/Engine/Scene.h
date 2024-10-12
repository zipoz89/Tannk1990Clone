#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

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

private:
	void LoadSceneFromLayout(nlohmann::json Content, nlohmann::json Legend);


	std::list<Entity*> m_Entities;
	std::string m_Name;
};