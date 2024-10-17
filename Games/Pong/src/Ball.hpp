#pragma once

#include "Entity.hpp"

#include <raylib.h>

namespace Classics
{
	class Ball : public Entity
	{
	public:
		Ball(Vector2 pos);

		void Update() override;
		void Draw() override;

		void Reset() noexcept;
		void ChangeXDirection() noexcept;

		Vector2 GetPos() const noexcept { return m_Pos; }
	private:
		Vector2 m_Pos;
		Vector2 m_OrigPos;
		Vector2 m_Speed;
		float m_Radius;
	};
}