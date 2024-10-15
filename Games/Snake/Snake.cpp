#include "Snake.hpp"

#include <raymath.h>

namespace Classics
{
	Snake::Snake(Vector2 pos) :
		m_Dir{ Direction::UP },
		m_Length{ Config::Snake::snakeInitialLength },
		m_Body{ Config::Snake::snakeInitialLength, {0} }
	{
		for (size_t i = 0; i < Config::Snake::snakeInitialLength; i++)
			m_Body[i] = { pos.x, pos.y + i };
	}

	void Snake::Update()
	{
		auto& head = m_Body[0];

		if (IsKeyDown(KEY_UP) && m_Dir != Direction::DOWN)
			m_Dir = Direction::UP;
		else if (IsKeyDown(KEY_LEFT) && m_Dir != Direction::RIGHT)
			m_Dir = Direction::LEFT;
		else if (IsKeyDown(KEY_DOWN) && m_Dir != Direction::UP)
			m_Dir = Direction::DOWN;
		else if (IsKeyDown(KEY_RIGHT) && m_Dir != Direction::LEFT)
			m_Dir = Direction::RIGHT;

		for (size_t i = m_Length - 1; i > 0; i--)
			m_Body[i] = m_Body[i - 1];

		head = Vector2Add(head, DirectionToVector2(m_Dir));
	}

	void Snake::Draw()
	{
		static constexpr size_t cellSize = Config::Snake::cellSize;

		for (size_t i = 0; i < m_Length; i++)
		{
			auto& pos = m_Body[i];
			DrawRectangleRec({ pos.x * cellSize + Config::gameBoxRect.x, pos.y * cellSize + Config::gameBoxRect.y, cellSize, cellSize }, SKYBLUE);
		}
	}

	void Snake::IncrementScore() noexcept
	{
		m_Body.resize(++m_Length * 2);
		m_Body[m_Length - 1] = m_Body[m_Length - 2];
	}

	bool Snake::IsSelfColliding() const noexcept
	{
		auto& head = m_Body[0];

		for (size_t i = 1; i < m_Length; i++)
			if (Vector2Equals(m_Body[i], head))
				return true;

		return false;
	}

	bool Snake::IsWallColliding() const noexcept
	{
		auto head = m_Body[0];

		return (
			head.x < 0 ||
			head.y < 0 ||
			head.x > Config::Snake::columns - 1 ||
			head.y > Config::Snake::rows - 1
			);
	}

	bool Snake::BodyContains(Vector2 pos) const noexcept
	{
		for (const auto& part : m_Body)
			if (Vector2Equals(part, pos))
				return true;

		return false;
	}
}