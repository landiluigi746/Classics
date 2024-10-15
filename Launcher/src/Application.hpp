#pragma once

#include "SceneManager.hpp"

namespace Classics
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		SceneManager m_SceneManager;
	};
}