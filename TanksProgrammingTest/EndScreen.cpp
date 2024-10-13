#include "EndScreen.h"

#include <iostream>
#include <SDL_rect.h>

#include "Entity.h"
#include "TextureComponent.h"


EndScreen::EndScreen(Entity* Owner) : EntityComponent(nullptr)
{
}

EndScreen::EndScreen() : EntityComponent(nullptr)
{
}

void EndScreen::Initialize()
{
    m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();

	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();
	m_InitialY = Rectangle.y;
}

void EndScreen::Update(float DeltaTime)
{
	m_ElapsedTime += DeltaTime;

	SDL_Rect& Rectangle = m_TextureComponent->GetRectangle();

	int offset = (sin(m_ElapsedTime * 3)) * 15;

	Rectangle.y = m_InitialY + offset;
}

