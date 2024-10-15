#include "Paddle.hpp"

#include "PongConfig.hpp"

#include <raymath.h>

namespace Classics
{
	Paddle::Paddle(Vector2 pos, int keyUp, int keyDown, bool AIMode) :
		m_Rect{ pos.x, pos.y, Config::Pong::paddleWidth, Config::Pong::paddleHeight },
		m_OrigPos{ pos },
		m_KeyUp{ keyUp },
		m_KeyDown{ keyDown },
		m_AIMode{ AIMode },
		m_Score{ 0 }
	{}

	void Paddle::Update()
	{
		if (m_AIMode)
		{
			AIUpdate();
			return;
		}

		float frameTime = GetFrameTime();

		if (IsKeyDown(m_KeyUp) && m_Rect.y > Config::gameBoxRect.y)
			m_Rect.y -= Config::Pong::paddleSpeed * frameTime;

		if (IsKeyDown(m_KeyDown) && m_Rect.y + m_Rect.height < Config::gameBoxRect.y + Config::gameBoxRect.height)
			m_Rect.y += Config::Pong::paddleSpeed * frameTime;

		if (m_Rect.y < Config::gameBoxRect.y)
			m_Rect.y = Config::gameBoxRect.y;

		if (m_Rect.y + m_Rect.height > Config::gameBoxRect.y + Config::gameBoxRect.height)
			m_Rect.y = Config::gameBoxRect.y + Config::gameBoxRect.height - m_Rect.height;
	}

	void Paddle::Draw()
	{
		DrawRectangleRounded(m_Rect, Config::Pong::roundness, 8, DARKGRAY);
	}

	void Paddle::Reset() noexcept
	{
		m_Rect = { m_OrigPos.x, m_OrigPos.y, Config::Pong::paddleWidth, Config::Pong::paddleHeight };
	}

	void Paddle::AIUpdate()
	{

	}
}