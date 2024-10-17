#include "SpaceInvadersScene.hpp"

#include <raylib.h>

namespace Classics
{
	SpaceInvadersScene::SpaceInvadersScene(SceneManager& sceneManager) :
		Scene{ sceneManager, 0.0 }
	{

	}

	void SpaceInvadersScene::OnUpdate()
	{

	}

	void SpaceInvadersScene::OnDraw()
	{
		ClearBackground(BLACK);
	}
}