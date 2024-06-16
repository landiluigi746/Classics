#ifndef CLASSICS_SPACEINVADERS_HPP
#define CLASSICS_SPACEINVADERS_HPP

#include <common/commons.hpp>

#define PLAYER_TEXTURE

namespace Classics
{
    class InvadersGame : public Program
    {
        public:
            InvadersGame(rl::Window& window):
                Program{window, "Space Invaders", rl::Color::Black()},
                level{1}
            {}

        private:
            static constexpr int textureSize = 48;
            static constexpr double defaultTick = 0.4f;

            static constexpr int rowInvaders = (boxWidth - offset) / (textureSize * 2);
            static constexpr int defaultLives = 3;
            static constexpr float playerSpeed = 4.0f;
            static constexpr float bulletSpeed = 6.0f;
            static constexpr float defaultInvadersSpeed = 0.2f;
            static constexpr int scores[] = {10, 25, 40, 120};

            static std::vector<std::vector<bool>> baseBarrier;
            static int barrierWidth;
            static int barrierHeight;
            static double tick;
            static float invadersSpeed;

            static inline rl::Vector4 gameBounds {gameBox.x + boxThickness, gameBox.y + boxThickness, offset + gameBox.width - boxThickness * 2, offset + gameBox.height - boxThickness * 2};
            static inline rl::Vector2 bulletDim {4, 12};
            static inline rl::Vector2 blockDim {4, 4};

            virtual void Start() override;
            virtual bool Update() override;
            virtual void End() override;

            void InitLevel();
            void InvadersBehavior();
            void BulletsBehavior();
            void InvadersShoot();
            void BarriersBehavior();
            bool InvadersWin();
            void Animations();
            void Sounds();

            class Player : public GameObjectTexturized
            {
                public:
                    Player(): GameObjectTexturized{-1, -1, TEXTURES_PATH(spaceinvaders) + "player.png"} {}
                    Player(float x, float y);

                    void Move();
                    void GainScore(int score) noexcept;
                    int GetScore() const noexcept;
                    int GetLives() const noexcept;
                    void DecrementLives() noexcept;
                
                private:
                    int _score;
                    int _lives;
                    rl::Vector2 _orig;
            };

            class Invader : public GameObjectTexturized
            {
                public:
                    Invader(): GameObjectTexturized{-1, -1, TEXTURES_PATH(spaceinvaders) + "invader1.png"} {}
                    Invader(float x, float y, int score, rl::Texture2D&& texture);

                    void Move(float speed = invadersSpeed) noexcept;
                    virtual void Draw() const override;
                    void ChangeFrame() noexcept;
                    void GoForward() noexcept;
                    int GetScore() const noexcept;
                    virtual rl::Rectangle GetRect() const override;
                
                private:
                    int _score;
                    int _frame;
                    Direction _dir;
            };

            class Bullet : public GameObjectRectangle
            {
                public:
                    Bullet(): GameObjectRectangle{-1, -1, -1, -1} {}
                    Bullet(float x, float y, Direction dir);

                    void Move() noexcept;
                    void Reset();
                    bool IsOut() const noexcept;
                    void ChangeFrame() noexcept;
                    bool CheckCollision(const rl::Rectangle& other) const;

                private:
                    int _frame;
                    Direction _dir;
            };

            class Barrier : public GameObject
            {
                friend class Bullet;
                public:
                    Barrier(): GameObject{-1, -1} {}
                    Barrier(float x, float y);

                    void Draw() const;
                    bool Exists() const noexcept;
                    std::list<rl::Vector2>& GetBlocks() noexcept;
                
                private:
                    std::list<rl::Vector2> _blocks;
            };

            int level;
            rl::Texture2D background;
            rl::Texture2D backgroundBuildings;

            rl::Music backgroundMusic;
            rl::Sound shootSound;
            rl::Sound specialInvaderSound;
            rl::Sound playerDeathSound;
            rl::Sound invaderKilledSound;

            Player player;
            Bullet playerBullet;
            Invader specialInvader;
            std::list<Invader> invaders;
            std::list<Bullet> invadersBullets;
            std::vector<Barrier> barriers;

            double curr_time;
    };
} // namespace Classics


#endif // !CLASSICS_SPACEINVADERS_HPP