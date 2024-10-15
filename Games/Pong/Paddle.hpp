#pragma once

#include "Entity.hpp"

#include <raylib.h>

namespace Classics
{
	class Paddle : public Entity
	{
	public:
		Paddle(Vector2 pos, int keyUp, int keyDown, bool AIMode = false);
	
		void Update() override;
		void Draw() override;

		void Reset() noexcept;
		void IncrementScore() noexcept { ++m_Score; }
		bool IsColliding(Vector2 pos, float radius) const noexcept { return CheckCollisionCircleRec(pos, radius, m_Rect); }

		size_t GetScore() const noexcept { return m_Score; }
	private:
		void AIUpdate();

		Rectangle m_Rect;
		Vector2 m_OrigPos;
		int m_KeyUp;
		int m_KeyDown;
		bool m_AIMode;
		size_t m_Score;
	};
}