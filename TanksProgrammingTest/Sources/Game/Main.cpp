#include "CollideeComponent.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "PlayerInputComponent.h"
#include "ColliderComponent.h"
#include "DestroyableComponent.h"
#include "ProjectileComponent.h"

int main(int argc, char* argv[])
{
	Engine::Get()->Initialize();

	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	ResourceManagerPtr->RegisterComponent("PlayerInputComponent", new PlayerInputComponent());
	ResourceManagerPtr->RegisterComponent("TextureComponent", new TextureComponent());
	ResourceManagerPtr->RegisterComponent("ColliderComponent", new ColliderComponent());
	ResourceManagerPtr->RegisterComponent("CollideeComponent", new CollideeComponent());
	ResourceManagerPtr->RegisterComponent("ProjectileComponent", new ProjectileComponent());
	ResourceManagerPtr->RegisterComponent("DestroyableComponent", new DestroyableComponent());

	Engine::Get()->CreateActiveSceneFromTemplate("MainScene");

	Engine::Get()->MainLoop();
	Engine::Get()->ShutDown();

	return 0;
}
