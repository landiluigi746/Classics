#ifndef CLASSICS_SNAKE_HPP
#define CLASSICS_SNAKE_HPP

#include <common/commons.hpp>

namespace Classics
{
    class SnakeGame : public Program
    {
        public:
            SnakeGame(rl::Window& window):
                Program{window, "Snake", rl::Color{173, 204, 96, 255}}
            {}
        private:
            static constexpr double tick = 0.07f;
            static constexpr int baseLength = 3;
            static constexpr int cellSize = 32;
            static constexpr int rowCells = boxHeight / cellSize;
            static constexpr int colCells = boxWidth / cellSize;

            virtual void Start() override;
            virtual bool Update() override;
            virtual void End() override;

            class Snake : public GameObjectRectangle
            {
                public:
                    Snake(): GameObjectRectangle{-1, -1, -1, -1} {}
                    Snake(int x, int y);
                    
                    void Move();
                    virtual void Draw(float roundness = 0.0f, int segments = 0) const override;
                    int GetScore() const noexcept;
                    void AddSegment() noexcept;
                    bool SelfCollision() const noexcept;
                    bool WallCollision() const noexcept;
                    bool Contains(rl::Vector2 pos) const noexcept;
                
                private:
                    std::vector<rl::Vector2> _body;
                    rl::Vector2 _dir;
                    int _length;
            };

            class Fruit : public GameObjectTexturized
            {
                public:
                    Fruit(): GameObjectTexturized{-1, -1, TEXTURES_PATH(snake) + "food.png"} {}
                    Fruit(const Snake& snake);

                    virtual void Draw() const override;
                    void ChangePos(const Snake& snake);
            };

            double curr_time;

            rl::Sound foodEatSound;
            rl::Sound deathSound;

            Snake snake;
            Fruit fruit;
    };
} // namespace Classics

#endif // !CLASSICS_SNAKE_HPP