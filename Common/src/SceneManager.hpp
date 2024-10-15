#pragma once

#include "Scene.hpp"

namespace Classics
{
	class SceneManager
	{
	public:
		SceneManager() = default;

		void UpdateDrawCurrentScene();

		template<typename SceneType, typename ...Args>
		void SwitchToScene(Args&&... args)
		{
			m_CurrentScene = std::move(CreateScene<SceneType>(*this, std::forward<Args>(args)...));
		}
	private:
		ScenePtr m_CurrentScene;
	};
}