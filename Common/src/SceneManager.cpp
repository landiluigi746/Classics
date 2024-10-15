#include "SceneManager.hpp"
#include "Config.hpp"

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

namespace Classics
{
	void SceneManager::UpdateDrawCurrentScene()
	{
		auto& scene = m_CurrentScene;

		if (scene == nullptr)
			return;
		
		double now = GetTime();

		if (now > scene->m_Time + scene->m_FrameTick)
		{
			scene->m_Time = now;

			for (const auto& [_, entity] : scene->m_Entities)
				entity->Update();

			scene->OnUpdate();
		}

		BeginDrawing();
		rlImGuiBegin();

		scene->OnDraw();

		for (const auto& [_, entity] : scene->m_Entities)
			entity->Draw();

		DrawRectangleLinesEx(Config::gameBoxBorder, Config::gameBoxBorderThickness, BLACK);

		DrawFPS(10, GetScreenHeight() - 30);

#ifdef DEBUG
		ImGui::Begin("Classics Scene Manager Debug");
		
		ImGui::Text("Scene: %s", GetTypeName<decltype(*scene)>().c_str());
		ImGui::Text("Entities: %zu", scene->m_Entities.size());

		for (const auto& [type, _] : scene->m_Entities)
			ImGui::Text("%s: %zu", type.c_str(), scene->m_Entities.count(type));

		ImGui::End();
#endif

		rlImGuiEnd();
		EndDrawing();
	}
}