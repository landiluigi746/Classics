#include "SceneManager.hpp"

namespace Classics
{
	void SceneManager::Init()
	{
		if (g_SceneManager != nullptr)
			return;

		g_SceneManager = new SceneManager();

		return;
	}

	void SceneManager::Shutdown()
	{
		if (g_SceneManager == nullptr)
			return;

		delete g_SceneManager;
		g_SceneManager = nullptr;

		return;
	}

	void SceneManager::UpdateDrawCurrentScene()
	{
		if (!m_CurrentScene.expired())
			m_CurrentScene.lock()->UpdateDraw();

		return;
	}

	bool SceneManager::IsCurrentSceneRunning()
	{
		return m_CurrentScene.lock()->IsRunning();
	}
}