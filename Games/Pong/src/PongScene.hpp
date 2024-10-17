#pragma once

#include "Scene.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"

namespace Classics
{
	class PongScene : public Scene
	{
	public:
		PongScene(SceneManager& sceneManager);

		void OnUpdate() override;
		void OnDraw() override;
	private:
		SharedPtr<Paddle> m_PaddleLeft;
		SharedPtr<Paddle> m_PaddleRight;
		SharedPtr<Ball> m_Ball;
	};
}