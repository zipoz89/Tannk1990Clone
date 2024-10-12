#include "CollideeComponent.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "PlayerInputComponent.h"
#include "ColliderComponent.h"
#include "DestroyableComponent.h"
#include "ProjectileComponent.h"
#include "Scene.h"
#include "TankControllerComponent.h"

int main(int argc, char* argv[])
{
	Engine::Get()->Initialize();

	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	ResourceManagerPtr->RegisterComponent("PlayerInputComponent", new PlayerInputComponent());
	ResourceManagerPtr->RegisterComponent("TankControllerComponent", new TankControllerComponent());
	ResourceManagerPtr->RegisterComponent("TextureComponent", new TextureComponent());
	ResourceManagerPtr->RegisterComponent("ColliderComponent", new ColliderComponent());
	ResourceManagerPtr->RegisterComponent("CollideeComponent", new CollideeComponent());
	ResourceManagerPtr->RegisterComponent("ProjectileComponent", new ProjectileComponent());
	ResourceManagerPtr->RegisterComponent("DestroyableComponent", new DestroyableComponent());
	ResourceManagerPtr->RegisterComponent("PoolableComponent", new PoolableComponent());

	Engine::Get()->CreateActiveSceneFromTemplate("MainScene");
	Engine::Get()->GetActiveScene()->AddPool("Projectile", 10);

	Engine::Get()->MainLoop();
	Engine::Get()->ShutDown();

	return 0;
}
