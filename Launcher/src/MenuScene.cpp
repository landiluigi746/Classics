#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Config.hpp"

#include "SnakeScene.hpp"
#include "PongScene.hpp"

#include <raylib.h>
#include <imgui.h>

namespace Classics
{
	MenuScene::MenuScene(SceneManager& sceneManager) :
		Scene{ sceneManager, GetFrameTime() }
	{}

	void MenuScene::OnDraw()
	{
		ClearBackground(BLACK);

		ImGui::SetNextWindowPos(ImVec2{ Config::gameBoxOffset, Config::gameBoxOffset });
		ImGui::SetNextWindowSize(ImVec2{ GetScreenWidth() - 128.0f, GetScreenHeight() - 128.0f });

		ImGui::Begin("Classics Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		if (ImGui::Button("Snake"))
			m_SceneManager.SwitchToScene<SnakeScene>();

		if (ImGui::Button("Pong"))
			m_SceneManager.SwitchToScene<PongScene>();

		if (ImGui::Button("Space Invaders"));

		if (ImGui::Button("Flappy Bird"));

		ImGui::End();
	}
}