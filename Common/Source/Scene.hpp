#pragma once

#include "Window.hpp"

namespace Classics
{
	class Scene
	{
	public:
		Scene() = default;

		virtual void Init() = 0;
		virtual bool IsRunning() = 0;
		virtual void Shutdown() = 0;

		void UpdateDraw()
		{
			Update();
			Draw();
		}
	protected:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}