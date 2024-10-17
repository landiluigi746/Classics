#include "PongScene.hpp"

#include "PongConfig.hpp"

#include "SceneManager.hpp"
#include "GameOverScene.hpp"

#include <raylib.h>
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

	PongScene::PongScene(SceneManager& sceneManager) :
		Scene{ sceneManager, 0.0 }
	{
		Vector2 pos1 = { Config::gameBoxRect.x, GetScreenHeight() / 2 - Config::Pong::paddleHeight / 2 };
		Vector2 pos2 = { Config::gameBoxRect.x + Config::gameBoxRect.width - Config::Pong::paddleWidth, GetScreenHeight() / 2 - Config::Pong::paddleHeight / 2 };

		m_PaddleLeft = AddEntity<Paddle>(pos1, KEY_W, KEY_S);
		m_PaddleRight = AddEntity<Paddle>(pos2, KEY_UP, KEY_DOWN);

		m_Ball = AddEntity<Ball>(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });
	}

	void PongScene::OnUpdate()
	{
		Vector2 ballPos = m_Ball->GetPos();
		static constexpr float ballRadius = Config::Pong::ballRadius;

		if (m_PaddleLeft->IsColliding(ballPos, ballRadius) || m_PaddleRight->IsColliding(ballPos, ballRadius))
			m_Ball->ChangeXDirection();

		bool outLeft = ballPos.x - ballRadius < Config::gameBoxRect.x;
		bool outRight = ballPos.x + ballRadius > Config::gameBoxRect.x + Config::gameBoxRect.width;

		if (outLeft || outRight)
		{
			m_PaddleLeft->Reset();
			m_PaddleRight->Reset();
			m_Ball->Reset();

			if (outLeft)
				m_PaddleRight->IncrementScore();
			else
				m_PaddleLeft->IncrementScore();
		}

		bool winLeft = m_PaddleLeft->GetScore() >= Config::Pong::winScore;
		bool winRight = m_PaddleRight->GetScore() >= Config::Pong::winScore;
	
		if (winLeft || winRight)
			m_SceneManager.SwitchToScene<GameOverScene>(TextFormat("Player %d wins", (winLeft) ? 1 : 2));
	}

	void PongScene::OnDraw()
	{
		ClearBackground(RAYWHITE);

		ImGui::SetNextWindowPos({ Config::gameBoxRect.x, Config::gameBoxRect.y / 4 });
		ImGui::SetNextWindowSize({ Config::gameBoxRect.width, 0 });

		ImGui::Begin("PongUI", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowFontScale(2.0f);

		ImGui::TextColored(rlImGuiColors::Convert(BLACK), "Score: %zu - %zu", m_PaddleLeft->GetScore(), m_PaddleRight->GetScore());

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