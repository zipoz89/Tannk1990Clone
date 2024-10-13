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

	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

	void Kill();
	bool IsKilled() const { return m_Killed; }

private:

	void HandleMovement(float DeltaTime);
	void HandleShooting(float DeltaTime);
	void Shoot();

	TextureComponent* m_TextureComponent;
	PlayerInputComponent* m_PlayerInputComponent;

	Direction m_CurrentDirection = UP;
	float m_FireCooldown = 0;
	float m_FireRate;
	int m_Speed;
	bool m_Killed;
};

