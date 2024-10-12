#pragma once

#include "ColliderComponent.h"
#include "EntityComponent.h"
#include "Float2.h"
#include "TankControllerComponent.h"

class TextureComponent;



class PlayerInputComponent : public ColliderComponent
{

public:
	PlayerInputComponent(Entity* Owner);
	PlayerInputComponent();

	virtual EntityComponent* Clone() const override { return new PlayerInputComponent(*this); }

	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Update(float DeltaTime) override;

	Float2 GetDirection() { return directionInput; }
	bool GetShooting() { return isShooting; }

private:
	std::list<Direction> m_DirectionInputBuffer;

	int upKey;
	int downKey;
	int leftKey;
	int rightKey;
	int shootKey;

	Float2 directionInput;
	bool isShooting;
};