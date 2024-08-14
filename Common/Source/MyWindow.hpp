// named MyWindow.hpp to differ from Window.hpp from raylib-cpp

#pragma once

#include "Window.hpp"

namespace Classics
{
	class Window : public raylib::Window
	{
	public:
		static void Init();
		static void Shutdown();

	private:
		Window();
	};

	inline Window* g_Window = nullptr;
}