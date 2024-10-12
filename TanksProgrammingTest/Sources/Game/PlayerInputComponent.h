#pragma once

#include "ColliderComponent.h"
#include "EntityComponent.h"

class TextureComponent;

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class PlayerInputComponent : public ColliderComponent
{

public:
	PlayerInputComponent(Entity* Owner);
	PlayerInputComponent();

	virtual EntityComponent* Clone() const override { return new PlayerInputComponent(*this); }

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	void Shoot();

private:
	TextureComponent* m_TextureComponent;
	Direction m_CurrentDirection = UP;
	float m_FireRate;
	float m_Speed;
	float m_FireCooldown;
};