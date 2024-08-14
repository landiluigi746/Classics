#include "MenuScene.hpp"

namespace Classics
{
	void MenuScene::Init()
	{

	}

	bool MenuScene::IsRunning()
	{
		return (!g_Window->ShouldClose());
	}

	void MenuScene::Update()
	{

	}

	void MenuScene::Draw()
	{
		g_Window->BeginDrawing();

		g_Window->ClearBackground(RAYWHITE);
		g_Window->DrawFPS();
		::DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		g_Window->EndDrawing();
	}

	void MenuScene::Shutdown()
	{

	}
}