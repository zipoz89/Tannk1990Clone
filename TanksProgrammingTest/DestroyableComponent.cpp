#include "DestroyableComponent.h"
#include "Entity.h"

void DestroyableComponent::Destroy()
{
	GetOwner()->Destroy();
}
