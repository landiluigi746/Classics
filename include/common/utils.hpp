#ifndef CLASSICS_COMMONS_UTILS_HPP
#define CLASSICS_COMMONS_UTILS_HPP

#include <raylib-cpp/raylib-cpp.hpp>
#include <list>
#include <memory>
#include <ctime>

namespace rl = raylib;

namespace Classics
{
    constexpr int windowWidth = 1024;
    constexpr int windowHeight = 768;
    constexpr int offset = windowWidth / 16;
    constexpr int boxWidth = windowWidth - offset * 2;
    constexpr int boxHeight = windowHeight - offset * 2;
    constexpr int boxThickness = 4;
    constexpr int spacing = 2;

    inline rl::Rectangle gameBox {offset - boxThickness, offset - boxThickness, boxWidth + boxThickness * 2, boxHeight + boxThickness * 2};
    inline rl::Vector4 gameBounds {gameBox.x + boxThickness, gameBox.y + boxThickness, offset + gameBox.width - boxThickness * 2, offset + gameBox.height - boxThickness * 2};
    inline rl::Vector2 center{(gameBounds.x + gameBounds.z) / 2, (gameBounds.y + gameBounds.w) / 2};

    enum class Direction
    {
        UP = 0,
        LEFT,
        DOWN,
        RIGHT
    };

    inline rl::Vector2 GetRandomVector2(int minX, int maxX, int minY, int maxY)
    { return {::GetRandomValue(minX, maxX), ::GetRandomValue(minY, maxY)}; }

    inline void Wait(uint32_t milliseconds)
    {
        std::clock_t start = std::clock();
        while(std::clock() - start < milliseconds);
        return;
    }
} // namespace Classics

#define RESOURCES_PATH std::string{"resources/"}
#define RESOURCES_GAME_PATH(game) RESOURCES_PATH + std::string{# game} + std::string{"/"}
#define TEXTURES_PATH(game) RESOURCES_GAME_PATH(game) + std::string{"textures/"}
#define SOUNDS_PATH(game) RESOURCES_GAME_PATH(game) + std::string{"sounds/"}

#endif // !CLASSICS_COMMONS_UTILS_HPP