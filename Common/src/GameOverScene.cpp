#include "GameOverScene.hpp"

#include <raylib.h>

namespace Classics
{
	static constexpr int fontSize = 20;
	static Vector2 textSize;

	GameOverScene::GameOverScene(SceneManager& sceneManager, const std::string& text) :
		Scene{ sceneManager, GetFrameTime() },
		m_Text{ text }
	{
		textSize = MeasureTextEx(GetFontDefault(), m_Text.c_str(), fontSize, 2);
	}

	void GameOverScene::OnDraw()
	{
		ClearBackground(RAYWHITE);
		DrawText(m_Text.c_str(), GetScreenWidth() / 2 - textSize.x / 2, GetScreenHeight() / 2 - textSize.y / 2, fontSize, BLACK);
	}
}