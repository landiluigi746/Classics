#pragma once

#include "Scene.hpp"

#include "Snake.hpp"
#include "Fruit.hpp"

namespace Classics
{
	class SnakeScene : public Scene
	{
	public:
		SnakeScene(SceneManager& sceneManager);

		void OnUpdate() override;
		void OnDraw() override;
	private:
		SharedPtr<Snake> m_Snake;
		SharedPtr<Fruit> m_Fruit;

		Sound m_EatSound;
		Sound m_LoseSound;

		Music m_Music;
	};
}