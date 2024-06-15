#include <games/snake.hpp>

namespace Classics
{
    void SnakeGame::Start()
    {
        snake = Snake(colCells / 2, rowCells / 2);
        fruit = Fruit(snake);
        curr_time = GetTime();

        sounds.resize(2);

        sounds[0] = rl::Sound{SOUNDS_PATH(snake) + "food_eat.ogg"};
        sounds[1] = rl::Sound{SOUNDS_PATH(snake) + "death.ogg"};

        p_window.SetTargetFPS(60);

        return;
    }

    bool SnakeGame::Update()
    {
        {
            if(GetTime() >= curr_time + tick)
            {
                curr_time = GetTime();
                snake.Move();

                if(snake.pos == fruit.pos)
                {
                    sounds[0].Play();
                    fruit.ChangePos(snake);

                    if(snake.GetScore() < rowCells * colCells)
                        snake.AddSegment();
                }

                if(snake.WallCollision() || snake.SelfCollision())
                {
                    sounds[1].Play();
                    return false;
                }
            }
        }

        p_window.BeginDrawing();

        {
            p_window.ClearBackground(p_bgColor);
            gameBox.DrawLines(rl::Color::DarkGray(), boxThickness);

            snake.Draw();
            fruit.Draw();

            fruit.texture.Draw(windowWidth / 2 - 32, offset / 4);

            char score[10];
            ::sprintf_s(score, "%d", snake.GetScore());
            ::DrawText(score, windowWidth / 2 + 32, offset / 4, 32, BLACK);
        }

        p_window.EndDrawing();

        return (!IsKeyDown(KEY_Q));
    }

    void SnakeGame::End()
    {
        while(!IsKeyDown(KEY_Q))
        {
            rl::Text text{::GetFontDefault(), "You lost", 30, spacing, rl::Color::Black()};
            rl::Vector2 textDim{text.MeasureEx()};

            p_window.BeginDrawing();

            p_window.ClearBackground(p_bgColor);
            text.Draw(center.x - textDim.x / 2, center.y - textDim.y / 2);

            p_window.EndDrawing();
        }

        return;
    }
} // namespace Classics