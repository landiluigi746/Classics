#include "Ball.hpp"

#include "PongConfig.hpp"
#include "Direction.hpp"

#include <raymath.h>

namespace Classics
{
	Ball::Ball(Vector2 pos) :
		m_Pos{ pos },
		m_OrigPos{ pos },
		m_Radius{ Config::Pong::ballRadius }
	{
		float directionX = GetRandomValue(0, 1) ? -1.0f : 1.0f;
		float directionY = GetRandomValue(0, 1) ? -1.0f : 1.0f;

		m_Speed = Vector2Scale(Vector2{ directionX, directionY }, Config::Pong::ballSpeed);
	}

	void Ball::Update()
	{
		m_Pos = Vector2Add(m_Pos, Vector2Scale(m_Speed, GetFrameTime()));

		if (m_Pos.y - m_Radius < Config::gameBoxRect.y)
		{
			m_Pos.y = Config::gameBoxRect.y + m_Radius;
			m_Speed.y *= -1.0f;
		}
		else if (m_Pos.y + m_Radius > Config::gameBoxRect.y + Config::gameBoxRect.height)
		{
			m_Pos.y = Config::gameBoxRect.y + Config::gameBoxRect.height - m_Radius;
			m_Speed.y *= -1.0f;
		}
	}

	void Ball::Draw()
	{
		DrawCircleV(m_Pos, m_Radius, ORANGE);
	}

	void Ball::Reset() noexcept
	{
		m_Pos = m_OrigPos;
	}

	void Ball::ChangeXDirection() noexcept
	{
		m_Speed.x *= -1.0f;
	}
}