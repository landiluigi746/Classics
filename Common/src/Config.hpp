#pragma once

#include <raylib.h>
#include <imgui.h>

namespace Classics::Config
{
	static constexpr int windowWidth = 1024;
	static constexpr int windowHeight = 768;

	static constexpr float gameBoxOffset = 64.0f;
	static constexpr float gameBoxWidth = windowWidth - gameBoxOffset * 2;
	static constexpr float gameBoxHeight = windowHeight - gameBoxOffset * 2;
	static constexpr float gameBoxBorderThickness = 3.0f;

	static constexpr Rectangle gameBoxRect = { gameBoxOffset, gameBoxOffset, gameBoxWidth, gameBoxHeight };
	static constexpr Rectangle gameBoxBorder = { gameBoxRect.x - gameBoxBorderThickness, gameBoxRect.y - gameBoxBorderThickness, gameBoxRect.width + gameBoxBorderThickness * 2, gameBoxRect.height + gameBoxBorderThickness * 2 };
}