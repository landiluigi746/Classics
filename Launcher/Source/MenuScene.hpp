#pragma once

#include "Scene.hpp"
#include "MyWindow.hpp"

namespace Classics
{
	class MenuScene : public Scene
	{
	public:
		MenuScene() = default;

		virtual void Init() override;
		virtual bool IsRunning() override;
		virtual void Shutdown() override;
	private:
		virtual void Update() override;
		virtual void Draw() override;
	};
}