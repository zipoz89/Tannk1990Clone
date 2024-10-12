#include "TextureComponent.h"
#include "Engine.h"

TextureComponent::TextureComponent(Entity* Owner)
	: EntityComponent(Owner)
	, m_Rectangle{ 0,0,0,0 }
{
}

TextureComponent::TextureComponent()
	: TextureComponent(nullptr)
{
}

void TextureComponent::LoadFromConfig(nlohmann::json Config)
{
	std::string TextureName = Config.value("Texture", "");
	if (!TextureName.empty())
	{
		SetTextureFromAssetName(TextureName);
	}

	m_Rectangle.w = Config.value("Width", 10);
	m_Rectangle.h = Config.value("Height", 10);
	m_Rectangle.x = Config.value("PositionX", 0);
	m_Rectangle.y = Config.value("PositionY", 0);
}

void TextureComponent::Initialize()
{
}

void TextureComponent::UnInitialize()
{
	SDL_DestroyTexture(m_Texture);
}

void TextureComponent::Draw()
{
	if (m_Texture) {
		SDL_RenderCopyEx(Engine::Get()->GetRenderer(), m_Texture, nullptr, &m_Rectangle, _angle, nullptr, SDL_FLIP_NONE);
	}

}

void TextureComponent::SetTextureFromAssetName(std::string Name)
{
	TexturePath = "Resources/Images/" + Name;

	// Load the texture once
	SDL_Surface* Surface = IMG_Load(TexturePath.c_str());
	if (!Surface) {
		SDL_Log("Failed to load surface: %s", IMG_GetError());
		return;
	}
	m_Texture = SDL_CreateTextureFromSurface(Engine::Get()->GetRenderer(), Surface);
	SDL_FreeSurface(Surface);

	if (!m_Texture) {
		SDL_Log("Failed to create texture: %s", SDL_GetError());
	}
}

void TextureComponent::SetPosition(int x, int y)
{
	m_Rectangle.x = x;
	m_Rectangle.y = y;
}

void TextureComponent::SetScale(int w, int h)
{
	m_Rectangle.w = w;
	m_Rectangle.h = h;
}

void TextureComponent::SetRotation(float angle)
{
	_angle = angle;
}