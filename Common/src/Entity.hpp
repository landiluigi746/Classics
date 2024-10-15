#pragma once

#include "Utils.hpp"

namespace Classics
{
	class Entity
	{
	public:
		Entity() = default;

		virtual ~Entity() {}

		virtual void Update() {}
		virtual void Draw() {}
	};
	
	using EntityPtr = SharedPtr<Entity>;

	template<typename EntityType, typename ...Args>
	EntityPtr CreateEntity(Args&&... args)
	{
		static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType is note derived from Entity!");
		return std::make_shared<EntityType>(std::forward<Args>(args)...);
	}
}