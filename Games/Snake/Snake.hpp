#pragma once

#include "Entity.hpp"
#include "Direction.hpp"
#include "SnakeConfig.hpp"

#include <raylib.h>
#include <vector>

namespace Classics
{
	class Snake : public Entity
	{
	public:
		Snake(Vector2 pos);

		void Update() override;
		void Draw() override;

		void IncrementScore() noexcept;
		bool IsSelfColliding() const noexcept;
		bool IsWallColliding() const noexcept;
		bool BodyContains(Vector2 pos) const noexcept;

		Vector2 GetPos() const noexcept { return m_Body[0]; }
		size_t GetScore() const noexcept { return m_Length - Config::Snake::snakeInitialLength; }
	private:
		Direction m_Dir;
		size_t m_Length;
		std::vector<Vector2> m_Body;
	};
}