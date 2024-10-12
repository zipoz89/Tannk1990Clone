#include "PoolManager.h"

#include <iostream>

#include "Engine.h"
#include "Scene.h"

PoolManager::PoolManager(const char* object_template, int initial_size)
{
    m_PoolTemplate = object_template;

    for (int i = 0; i < initial_size; ++i)
    {
        PoolableComponent* newObject = Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate(m_PoolTemplate, 0, 0, 10, 10)->GetComponent<PoolableComponent>();
        newObject->OnReturnedToPool();  // Mark objects as inactive
        m_Pool.push(newObject);
    }
}

PoolableComponent* PoolManager::GetEntity()
{
    if (m_Pool.empty())
    {
        // Create more if the pool is empty
        PoolableComponent* newObject = Engine::Get()->GetActiveScene()->SpawnEntityFromTemplate(m_PoolTemplate, 0, 0, 10, 10)->GetComponent<PoolableComponent>();
        newObject->OnGetToPool();  // Activate the object
        return newObject;
    }
    else
    {
        PoolableComponent* object = m_Pool.front();
        m_Pool.pop();
        object->OnGetToPool();  // Activate the object
        return object;
    }
}

void PoolManager::ReturnEntity(PoolableComponent* object)
{
    object->OnReturnedToPool();  // Reset and deactivate the object
    m_Pool.push(object);         // Return it to the pool
}
