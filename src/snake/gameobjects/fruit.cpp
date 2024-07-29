#include <games/snake.hpp>

namespace Classics
{
    SnakeGame::Fruit::Fruit(const SnakeGame::Snake& snake):
        GameObjectTexturized{-1, -1, TEXTURES_PATH(snake) + "food.png"}
    {
        do{
            pos = GetRandomVector2(1, colCells - 1, 1, rowCells - 1);
        } while(snake.Contains(pos));
    }

    void SnakeGame::Fruit::Draw() const
    {
        texture.Draw(offset + pos.x * cellSize, offset + pos.y * cellSize);
        return;
    }

    void SnakeGame::Fruit::ChangePos(const SnakeGame::Snake& snake)
    {
        do{
            pos = GetRandomVector2(1, colCells - 1, 1, rowCells - 1);
        } while(snake.Contains(pos));

        return;
    }
} // namespace Classics