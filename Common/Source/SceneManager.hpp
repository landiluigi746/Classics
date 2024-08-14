#pragma once

#include "Scene.hpp"

#include <unordered_map>
#include <memory>

namespace Classics
{
	class SceneManager
	{
	public:
		static void Init();
		static void Shutdown();

		template<typename SceneType, typename = std::enable_if_t<std::is_base_of<Scene, SceneType>::value, bool>>
		void AddScene(bool setCurrent = true)
		{
			auto scenePtr = std::make_shared<SceneType>();

			m_ScenesMap.emplace(typeid(SceneType).name(), scenePtr);

			if (setCurrent)
			{
				if (!m_CurrentScene.expired())
					m_CurrentScene.lock()->Shutdown();

				m_CurrentScene = scenePtr;
				m_CurrentScene.lock()->Init();
			}

			return;
		}

		template<typename SceneType, typename = std::enable_if_t<std::is_base_of<Scene, SceneType>::value, bool>>
		void SwitchToScene()
		{
			auto it = m_ScenesMap.find(typeid(SceneType).name());

			if (it != m_ScenesMap.end())
				return;

			if (!m_CurrentScene.expired())
				m_CurrentScene.lock()->Shutdown();

			m_CurrentScene = it->second;
			m_CurrentScene.lock()->Init();

			return;
		}

		template<typename SceneType, typename = std::enable_if_t<std::is_base_of<Scene, SceneType>::value, bool>>
		void RemoveScene()
		{
			auto it = m_ScenesMap.find(typeid(SceneType).name());

			if (it != m_ScenesMap.end())
				return;

			m_ScenesMap.erase(it);

			return;
		}

		void UpdateDrawCurrentScene();
		bool IsCurrentSceneRunning();
	private:
		SceneManager() = default;

		std::weak_ptr<Scene> m_CurrentScene;
		std::unordered_map<std::string, std::shared_ptr<Scene>> m_ScenesMap;
	};

	inline SceneManager* g_SceneManager = nullptr;
}