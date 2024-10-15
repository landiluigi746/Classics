#pragma once

#include <raylib.h>

namespace Classics
{
	enum class Direction
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	inline constexpr Vector2 DirectionToVector2(Direction dir)
	{
		Vector2 result = { 0, 0 };

		switch (dir)
		{
		case Direction::UP: result = { 0, -1 }; break;
		case Direction::LEFT: result = { -1, 0 }; break;
		case Direction::DOWN: result = { 0, 1 }; break;
		case Direction::RIGHT: result = { 1, 0 }; break;
		}

		return result;
	}
}