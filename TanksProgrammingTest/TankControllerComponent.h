#pragma once
#include "ColliderComponent.h"

class PlayerInputComponent;
class TextureComponent;

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class TankControllerComponent : public ColliderComponent
{
public:
	TankControllerComponent(Entity* Owner);
	TankControllerComponent();

	virtual EntityComponent* Clone() const override { return new TankControllerComponent(*this); }

	virtual void Initialize() override;
	virtual void UnInitialize() override;
	void HandleMovement(float DeltaTime);
	void HandleShooting(float DeltaTime);
	virtual void Update(float DeltaTime) override;
	void Shoot();

private:
	TextureComponent* m_TextureComponent;
	PlayerInputComponent* m_PlayerInputComponent;
	Direction m_CurrentDirection = UP;
	float m_FireRate;
	float m_Speed;
	float m_FireCooldown;

	bool m_Destroyed;
};

