#include "PoolableComponent.h"

#include "Entity.h"
#include "TextureComponent.h"

void PoolableComponent::OnReturnedToPool()
{
	m_IsActive = false;
	GetOwner()->GetComponent<TextureComponent>()->SetVisible(false);
}

void PoolableComponent::OnGetToPool()
{
	m_IsActive = true;
	GetOwner()->GetComponent<TextureComponent>()->SetVisible(true);
}
