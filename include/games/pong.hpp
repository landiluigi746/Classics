#ifndef CLASSICS_PONG_HPP
#define CLASSICS_PONG_HPP

#include <common/commons.hpp>

namespace Classics
{
    class PongGame : public Program
    {
        public:
            PongGame(rl::Window& window):
                Program{window, "Pong", rl::Color::RayWhite()},
                winner{0}
            {}
        private:
            static constexpr int maximumScore = 20;
            static constexpr int paddleWidth = 20;
            static constexpr int paddleHeight = 128;
            static constexpr float paddleSpeed = 20.0f;
            static constexpr int ballSize = 20;
            static constexpr float ballSpeed = 9.5f;
            
            static std::vector<rl::Sound> sounds;

            virtual void Start() override;
            virtual bool Update() override;
            virtual void End() override;

            class Paddle : public GameObjectRectangle
            {
                public:
                    Paddle(): GameObjectRectangle{-1, -1, -1, -1} {}
                    Paddle(float x, float y, int keyUp, int keyDown);

                    void Move();
                    void Reset() noexcept;
                    void IncrementScore() noexcept;
                    int GetScore() const noexcept;
                
                private:
                    int _keyUp;
                    int _keyDown;
                    int _score;
                    Vector2 _orig;
            };

            class Ball : public GameObjectRectangle
            {
                public:
                    Ball(): GameObjectRectangle{-1, -1, -1, -1} {}
                    Ball(float x, float y);

                    void Move() noexcept;
                    void Reset() noexcept;
                    bool Out() const noexcept;
                    bool OutLeft() const noexcept;
                    void Collision(const Paddle& paddle) noexcept;
                
                private:
                    Vector2 _speed;
                    Vector2 _orig;
            };

            int winner;
            
            Ball ball;
            Paddle player1;
            Paddle player2;
    };
} // namespace Classics


#endif // !CLASSICS_PONG_HPP