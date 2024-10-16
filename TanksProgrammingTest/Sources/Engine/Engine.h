#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <vector>
#include <string>

#include "IState.h"

class Scene;
class ResourceManager;

class Engine
{

public:
	static Engine* Get();

	void Initialize(std::unique_ptr<IState> initialGameState);
	void MainLoop();
	void Draw();
	void ShutDown();

	SDL_Renderer* GetRenderer() { return m_Renderer; }
	SDL_Window* GetWindow() { return m_Window; }
	ResourceManager* GetResourceManager() { return m_ResourceManager; }
	const std::vector<SDL_Event>& GetEvents() { return m_Events; }
	void SetActiveScene(Scene* Scene) { m_ActiveScene = Scene; }
	Scene* GetActiveScene() { return m_ActiveScene; }
	void CreateActiveSceneFromTemplate(std::string Name);

	void SetGameState(std::unique_ptr<IState> newState);
	IState* GetGameState() const { return m_CurrentState.get(); }

private:
	Engine();

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Scene* m_ActiveScene;
	ResourceManager* m_ResourceManager;

	unsigned int FramesPerSecond;
	unsigned int TimePerFrameInMs;
	float TimePerFramInSceonds;

	std::vector<SDL_Event> m_Events;

	std::unique_ptr<IState> m_CurrentState;
};