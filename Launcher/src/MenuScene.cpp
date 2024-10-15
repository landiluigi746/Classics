#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Config.hpp"

#include "SnakeScene.hpp"
#include "PongScene.hpp"

#include "UI.hpp"

#include <raylib.h>

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
		ImGui::SetWindowFontScale(2.0f);

		CENTER(ImGui::Text("Classics"), 0.0f, 20.0f, 20.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

		if (CENTER(ImGui::Button("Snake"), 0.0f, 20.0f, 20.0f))
			m_SceneManager.SwitchToScene<SnakeScene>();

		if (CENTER(ImGui::Button("Pong"), 0.0f, 20.0f, 20.0f))
			m_SceneManager.SwitchToScene<PongScene>();

		if (CENTER(ImGui::Button("Space Invaders"), 0.0f, 20.0f, 20.0f));

		if (CENTER(ImGui::Button("Flappy Bird"), 0.0f, 20.0f, 20.0f));

		ImGui::PopStyleColor();

		ImGui::End();
	}
}