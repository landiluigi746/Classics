#pragma once

#include "Entity.hpp"
#include "Utils.hpp"

#include <unordered_map>

namespace Classics
{
	class SceneManager;

	class Scene
	{
	public:
		Scene(SceneManager& sceneManager, double frameTick) :
			m_SceneManager{ sceneManager },
			m_FrameTick{ frameTick },
			m_Time{ 0.0f }
		{}

		virtual ~Scene() {}

		virtual void OnUpdate() {}
		virtual void OnDraw() = 0;
	protected:
		template<typename EntityType, typename ...Args>
		SharedPtr<EntityType> AddEntity(Args&&... args)
		{
			auto entity = CreateEntity<EntityType>(std::forward<Args>(args)...);
			m_Entities.emplace(GetTypeName<EntityType>(), entity);
			return std::dynamic_pointer_cast<EntityType>(entity);
		}

		template<typename EntityType>
		std::vector<EntityPtr> GetEntities()
		{
			auto range = m_Entities.equal_range(GetTypeName<EntityType>());
			std::vector<EntityPtr> ret(range.first, range.second);

			return ret;
		}

		SceneManager& m_SceneManager;
	private:
		std::hash<std::string> m_Hasher;
		std::unordered_multimap<std::string, EntityPtr> m_Entities;

		double m_FrameTick;
		double m_Time;

		friend class SceneManager;
	};

	using ScenePtr = UniquePtr<Scene>;

	template<typename SceneType, typename ...Args>
	ScenePtr CreateScene(SceneManager& sceneManager, Args&&... args)
	{
		static_assert(std::is_base_of<Scene, SceneType>::value, "SceneType is not derived from Scene");
		return std::make_unique<SceneType>(sceneManager, std::forward<Args>(args)...);
	}

	// NOTE: MenuScene is defined here so that it's easily accessible from the games
	// Implemented in Launcher
	class MenuScene : public Scene
	{
	public:
		MenuScene(SceneManager& sceneManager);

		void OnDraw() override;
	};
}