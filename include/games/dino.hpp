#ifndef CLASSICS_DINO_HPP
#define CLASSICS_DINO_HPP

#include <common/commons.hpp>

namespace Classics
{
    class DinoGame : public Program
    {
        public:
            DinoGame(rl::Window& window):
                Program{window, "Dino"}
            {}
        private:
            static constexpr float jumpTick = 1.0f;
            static constexpr float spawnTick = 1.5f;
            static constexpr double frameTick = 0.064f;

            static constexpr float gravity = 165.0f;

            static constexpr float obstacleSpeed = 6.0f;

            static float groundEndY;

            virtual void Start();
            virtual bool Update();
            virtual void End();

            void Animations();

            class Runner : public GameObjectTexturized
            {
                public:
                    Runner(): GameObjectTexturized{center.x, center.y, TEXTURES_PATH(dino) + "dino-up.png"} {}
                    Runner(float x, float y);

                    void Move();
                    virtual void Draw() const override;
                    void ChangeFrame() noexcept;
                    virtual rl::Rectangle GetRect() const override;

                private:
                    rl::Texture upTexture;
                    rl::Texture downTexture;

                    int _frame;
                    bool _down;
                    bool _jumping;
                    float _acceleration;
                    float _velocity;
            };

            class Obstacle : public GameObjectTexturized
            {
                public:
                    Obstacle(): GameObjectTexturized{-1, -1, TEXTURES_PATH(dino) + "cactus1.png"} {}
                    Obstacle(float x, bool init = true);

                    void Move();
                    virtual void Draw() const override;
                    bool Exists() const noexcept;
                    virtual void ChangeFrame() {}
                    bool IsColliding(const Runner& runner) const noexcept;

                    bool passed;
                private:
            };

            class Bird : public Obstacle
            {
                public:
                    Bird(): Obstacle{-1, false} {}
                    Bird(float x);

                    virtual void Draw() const override;
                    virtual void ChangeFrame() noexcept;
                private:
                    int _frame;
            };

            rl::Sound hitSound;
            static rl::Sound pressSound;

            float groundScroll;
            float cloudsScroll;

            double curr_time;
            double spawn_time;

            int score;

            rl::Texture2D ground;
            rl::Texture2D clouds;

            Runner runner;
            std::list<Obstacle> obstacles;
    };
} // namespace Classics

#endif // !CLASSICS_DINO_HPP