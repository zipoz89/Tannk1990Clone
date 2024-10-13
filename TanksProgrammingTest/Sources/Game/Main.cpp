#include "CollideeComponent.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "PlayerInputComponent.h"
#include "ColliderComponent.h"
#include "DestroyableComponent.h"
#include "EmptyState.h"
#include "EndScreen.h"
#include "PlayingState.h"
#include "ProjectileComponent.h"
#include "Scene.h"
#include "TankControllerComponent.h"

int main(int argc, char* argv[])
{
	Engine::Get()->Initialize(std::make_unique<EmptyState>());

	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	ResourceManagerPtr->RegisterComponent("PlayerInputComponent", new PlayerInputComponent());
	ResourceManagerPtr->RegisterComponent("TankControllerComponent", new TankControllerComponent());
	ResourceManagerPtr->RegisterComponent("TextureComponent", new TextureComponent());
	ResourceManagerPtr->RegisterComponent("ColliderComponent", new ColliderComponent());
	ResourceManagerPtr->RegisterComponent("CollideeComponent", new CollideeComponent());
	ResourceManagerPtr->RegisterComponent("ProjectileComponent", new ProjectileComponent());
	ResourceManagerPtr->RegisterComponent("DestroyableComponent", new DestroyableComponent());
	ResourceManagerPtr->RegisterComponent("PoolableComponent", new PoolableComponent());
	ResourceManagerPtr->RegisterComponent("EndScreen", new EndScreen());

	Engine::Get()->SetGameState(std::make_unique<PlayingState>());

	Engine::Get()->MainLoop();
	Engine::Get()->ShutDown();

	return 0;
}
