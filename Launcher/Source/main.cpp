#include "raylib-cpp.hpp"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	raylib::Window window(screenWidth, screenHeight, "raylib [core] example - basic window");
	window.SetTargetFPS(60);

	while (!window.ShouldClose())
	{
		window.BeginDrawing();

		window.ClearBackground(RAYWHITE);
		::DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		window.EndDrawing();
	}

	return 0;
}