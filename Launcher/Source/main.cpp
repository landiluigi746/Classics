#include "raylib-cpp.hpp"

#include "SceneManager.hpp"
#include "MenuScene.hpp"
#include "Config.hpp"

namespace Classics
{
	static void RunLauncher()
	{
		Window::Init();
		SceneManager::Init();

		g_Window->SetTargetFPS(60);
		g_SceneManager->AddScene<MenuScene>();

		while (g_SceneManager->IsCurrentSceneRunning())
			g_SceneManager->UpdateDrawCurrentScene();

		Window::Shutdown();
		SceneManager::Shutdown();

		return;
	}
}

int main()
{
	Classics::RunLauncher();
	return 0;
}