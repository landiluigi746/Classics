#include "Fruit.hpp"

#include <raymath.h>

namespace Classics
{
	Fruit::Fruit(SharedPtr<Snake> snake) :
		m_Snake{ snake }
	{
		ChangePosition();
	}

	void Fruit::Draw()
	{
		static constexpr size_t cellSize = Config::Snake::cellSize;
		DrawRectangleRec({ m_Pos.x * cellSize + Config::gameBoxRect.x, m_Pos.y * cellSize + Config::gameBoxRect.y, cellSize, cellSize }, RED);
	}

	void Fruit::ChangePosition()
	{
		do {
			m_Pos = { (float)GetRandomValue(1, (int)Config::Snake::columns - 1), (float)GetRandomValue(1, (int)Config::Snake::rows - 1) };
		} while (m_Snake->BodyContains(m_Pos));
	}
}