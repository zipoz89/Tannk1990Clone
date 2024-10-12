#pragma once
#include "EntityComponent.h"
#include "SDL.h"

class ColliderComponent : public EntityComponent
{

public:
	ColliderComponent(Entity* Owner);
	ColliderComponent();

	virtual EntityComponent* Clone() const override { return new ColliderComponent(*this); }

	virtual void Initialize() override;
	//virtual void Update(float DeltaTime) override;
	void SetColliderSize(int Width, int Height);
	bool IsColliding(const SDL_Rect& OtherRect);
	
	SDL_Rect& GetCollider() { return m_Collider; }

protected:
	void UpdatePoition();
	SDL_Rect m_Collider;  // Collision bounds
};