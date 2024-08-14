#include "MyWindow.hpp"
#include "Config.hpp"

namespace Classics
{
	Window::Window():
		raylib::Window{windowConfig.width, windowConfig.height, windowConfig.title, windowConfig.flags}
	{}

	void Window::Init()
	{
		if (g_Window != nullptr)
			return;

		g_Window = new Window();

		return;
	}

	void Window::Shutdown()
	{
		if (g_Window == nullptr)
			return;

		delete g_Window;
		g_Window = nullptr;
	}
}