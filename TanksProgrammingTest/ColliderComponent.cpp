#include "ColliderComponent.h"

#include <iostream>

#include "Entity.h"
#include "TextureComponent.h"

ColliderComponent::ColliderComponent(Entity* Owner)
    : EntityComponent(Owner)
    , m_Collider{ 0, 0, 0, 0 }
{
}

ColliderComponent::ColliderComponent()
    : ColliderComponent(nullptr)
{
}

void ColliderComponent::Initialize()
{
    TextureComponent* TextureComp = GetOwner()->GetComponent<TextureComponent>();
    if (TextureComp)
    {
        m_Collider = TextureComp->GetRectangle();  // Initialize based on the texture

        //std::cout << "setting collider" << m_Collider.w << " " << m_Collider.h << "\n";
    }
}


void ColliderComponent::SetColliderSize(int Width, int Height)
{
    m_Collider.w = Width;
    m_Collider.h = Height;
}

bool ColliderComponent::IsColliding(const SDL_Rect& OtherRect)
{
    //std::cout << "Checking collison";

    return SDL_HasIntersection(&m_Collider, &OtherRect);
}

void ColliderComponent::UpdatePoition()
{
    TextureComponent* textureComponent = GetOwner()->GetComponent<TextureComponent>();
    if (textureComponent)
    {
        // Update collider position based on the entity's texture position
        SDL_Rect& entityRect = textureComponent->GetRectangle();
        m_Collider.x = entityRect.x;
        m_Collider.y = entityRect.y;
    }
}