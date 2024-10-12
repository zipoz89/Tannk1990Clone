#pragma once
#include <queue>
#include "PoolableComponent.h"


class PoolManager
{
public:
    PoolManager(const char* object_template, int initial_size);

    PoolableComponent* GetEntity();
    void ReturnEntity(PoolableComponent* object);


private:
    std::queue<PoolableComponent*> m_Pool;  // Pool of inactive objects
    std::string m_PoolTemplate;  // Pool of inactive objects
};
