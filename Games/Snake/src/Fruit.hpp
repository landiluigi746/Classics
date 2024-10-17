#pragma once

#include "Snake.hpp"

namespace Classics
{
	class Fruit : public Entity
	{
	public:
		Fruit(SharedPtr<Snake> snake);

		void Draw() override;

		void ChangePosition();

		Vector2 GetPos() const noexcept { return m_Pos; }
	private:
		Vector2 m_Pos;

		SharedPtr<Snake> m_Snake;
	};
}