#pragma once

#include "Scene.hpp"

namespace Classics
{
	class GameOverScene : public Scene
	{
	public:
		GameOverScene(SceneManager& sceneManager, const std::string& text);

		void OnDraw() override;
	private:
		std::string m_Text;
	};
}