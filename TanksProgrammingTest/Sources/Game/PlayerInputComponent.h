#pragma once

#include "ColliderComponent.h"
#include "EntityComponent.h"
#include "Float2.h"
#include "TankControllerComponent.h"

class TextureComponent;


//this class can be generalized to be used as strategy pattern and made so that tank will be controlled by ai
class PlayerInputComponent : public EntityComponent
{
public:
	PlayerInputComponent(Entity* Owner);
	PlayerInputComponent();

	virtual EntityComponent* Clone() const override { return new PlayerInputComponent(*this); }

	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Update(float DeltaTime) override;

	Float2 GetDirection() { return m_DirectionInput; }
	bool GetShooting() { return m_IsShooting; }

private:
	std::list<Direction> m_DirectionInputBuffer;

	int m_UpKey;
	int m_DownKey;
	int m_LeftKey;
	int m_RightKey;
	int m_ShootKey;

	Float2 m_DirectionInput;
	bool m_IsShooting;
};