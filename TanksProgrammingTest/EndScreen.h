#pragma once
#include "EntityComponent.h"
class TextureComponent;

class EndScreen :
    public EntityComponent
{
public:
	EndScreen(Entity* Owner);
	EndScreen();

	virtual EntityComponent* Clone() const override { return new EndScreen(*this); }

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
private:
	TextureComponent* m_TextureComponent;
	float m_ElapsedTime = 0;
	int m_InitialY = 0;
};

