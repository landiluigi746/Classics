#ifndef CLASSICS_FLAPPYBIRD_HPP
#define CLASSICS_FLAPPYBIRD_HPP

#include <common/commons.hpp>

namespace Classics
{
    class FlappyBirdGame : public Program
    {
        public:
            FlappyBirdGame(rl::Window& window):
                Program{window, "Flappy Bird", rl::Color::RayWhite()}
            {}
        private:
            static constexpr float baseHeight = 112.0f;
            static constexpr float pipeHeight = 320.0f;
            static constexpr float minPipeHeight = pipeHeight / 4;
            static constexpr float pipeSpeed = 4.0f;

            static constexpr float jumpTick = 0.17f;
            static constexpr float frameTick = 0.048f;
            static double tick;

            static constexpr float gravity = 200.0f;
            static constexpr float playerJumpForce = 220.0f;
            
            static constexpr float downRotation = 90.0f;
            static constexpr float jumpRotation = -45.0f;

            static constexpr float scaleFactor = 1.7f;

            virtual void Start();
            virtual bool Update();
            virtual void End();

            class Player : public GameObjectTexturized
            {
                public:
                    Player(): GameObjectTexturized{-1, -1, TEXTURES_PATH(flappybird) + "player.png"} {}
                    Player(float x, float y);

                    void Move();
                    virtual void Draw() const override;
                    void ChangeFrame();
                    bool GroundColliding() const noexcept;
                
                private:
                    int _frame;
                    double _timer;
                    float _rotation;
            };

            class Obstacle : public GameObjectTexturized
            {
                public:
                    Obstacle(): GameObjectTexturized{-1, -1, TEXTURES_PATH(flappybird) + "pipe.png"} {}
                    Obstacle(float x, float y);

                    void Move();
                    virtual void Draw() const override;
                    bool Exists() const noexcept;
                    bool IsColliding(const Player& player) const noexcept;
                
                    bool passed;
                private:
                    float _upperPipeHeight;
                    float _lowerPipeHeight;
            };

            rl::Texture2D base;
            rl::Texture2D background;

            rl::Sound pointSound;
            rl::Sound hitSound;
            rl::Sound dieSound;
            static rl::Sound wingSound;

            static double curr_time;
            double curr_frame_time;

            float baseScroll;
            float bgScroll;

            rl::Camera2D camera;

            int score;

            Player player;
            std::list<Obstacle> obstacles;
    };
} // namespace Classics

#endif // !CLASSICS_FLAPPYBIRD_HPP