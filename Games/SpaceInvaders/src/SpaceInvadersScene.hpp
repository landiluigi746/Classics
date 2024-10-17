#pragma once

#include "Scene.hpp"

namespace Classics
{
	class SpaceInvadersScene : public Scene
	{
	public:
		SpaceInvadersScene(SceneManager& sceneManager);

		void OnUpdate() override;
		void OnDraw() override;
	private:
	};
}