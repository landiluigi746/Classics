#include "SnakeScene.hpp"
#include "SceneManager.hpp"

#include "SnakeConfig.hpp"

#include "GameOverScene.hpp"

#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <rlImGuiColors.h>

namespace Classics
{
	static constexpr Color boardColor = { 173, 204, 96, 255 };
	static constexpr std::pair<ImGuiCol, Color> buttonColors[] = {
		{ ImGuiCol_Button, { 156, 9, 19, 255 } },
		{ ImGuiCol_ButtonHovered, RED },
		{ ImGuiCol_ButtonActive, { 158, 36, 44, 255 } }
	};

	static constexpr float menuButtonSize = 135.0f;

	SnakeScene::SnakeScene(SceneManager& sceneManager) :
		Scene{ sceneManager, Config::Snake::tick }
	{
		Vector2 pos = { Config::Snake::columns / 2, Config::Snake::rows / 2 };
		m_Snake = AddEntity<Snake>(pos);
		m_Fruit = AddEntity<Fruit>(m_Snake);
	}

	void SnakeScene::OnUpdate()
	{
		if (Vector2Equals(m_Snake->GetPos(), m_Fruit->GetPos()))
		{
			m_Fruit->ChangePosition();
			m_Snake->IncrementScore();
		}

		if (m_Snake->IsSelfColliding() || m_Snake->IsWallColliding())
		{
			m_SceneManager.SwitchToScene<GameOverScene>(TextFormat("Score: %zu", m_Snake->GetScore()));
		}
	}

	void SnakeScene::OnDraw()
	{
		ClearBackground(boardColor);

		ImGui::SetNextWindowPos({ Config::gameBoxRect.x, Config::gameBoxRect.y / 4 });
		ImGui::SetNextWindowSize({ Config::gameBoxRect.width, 0 });
		
		ImGui::Begin("SnakeUI", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowFontScale(2.0f);

		ImGui::Text("Score: %zu", m_Snake->GetScore());

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() - menuButtonSize);

		for (const auto& [imguiCol, color] : buttonColors)
			ImGui::PushStyleColor(imguiCol, rlImGuiColors::Convert(color));

		if (ImGui::Button("Menu", { 125.0f, 0 }) || IsKeyPressed(KEY_Q))
			m_SceneManager.SwitchToScene<MenuScene>();

		ImGui::PopStyleColor(IM_ARRAYSIZE(buttonColors));

		ImGui::End();
	}
}