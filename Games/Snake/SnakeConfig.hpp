#pragma once

#include "Config.hpp"

namespace Classics::Config::Snake
{
	static constexpr float cellSize = 32.0f;

	static constexpr size_t columns = gameBoxWidth / cellSize;
	static constexpr size_t rows = gameBoxHeight / cellSize;

	static constexpr size_t snakeInitialLength = 3;
	static constexpr double tick = 0.06;
}