#pragma once

#include "EntityComponent.h"
#include "Engine.h"

class TextureComponent : public EntityComponent
{

public:
	TextureComponent(Entity* Owner);
	TextureComponent();

	virtual EntityComponent* Clone() const override { return new TextureComponent(*this); }

	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Initialize() override;
	virtual void UnInitialize() override;
	virtual void Draw() override;

	void SetTextureFromAssetName(std::string Name);
	void SetPosition(int x, int y);
	void SetScale(int w, int h);
	void SetRotation(float angle);
	SDL_Rect& GetRectangle() { return m_Rectangle; }
	void SetVisible(bool visible) { m_isVisible = visible; }

private:
	std::string TexturePath;
	SDL_Rect m_Rectangle;
	SDL_Texture* m_Texture;
	float m_angle;
	bool m_isVisible;
};