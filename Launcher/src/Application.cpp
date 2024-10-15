#include "Application.hpp"
#include "Config.hpp"

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <rlImGuiColors.h>

namespace Classics
{
	constexpr auto propertyField = IM_COL32(15, 15, 15, 255);

	Application::Application()
	{
		InitWindow(Config::windowWidth, Config::windowHeight, "Classics");
		rlImGuiSetup(true);

		auto& style = ImGui::GetStyle();
		style.FrameRounding = 12.0f;

		auto& colors = style.Colors;
	}

	void Application::Run()
	{
		m_SceneManager.SwitchToScene<MenuScene>();

		while (!WindowShouldClose())
			m_SceneManager.UpdateDrawCurrentScene();
	}

	Application::~Application()
	{
		rlImGuiShutdown();
		CloseWindow();
	}
}