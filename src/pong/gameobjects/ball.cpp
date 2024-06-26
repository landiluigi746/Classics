#include <games/pong.hpp>

namespace Classics
{
    PongGame::Ball::Ball(float x, float y):
        GameObjectRectangle{x, y, ballSize, ballSize, rl::Color::Orange()},
        _speed{ballSpeed, ballSpeed},
        _orig{x, y}
    {}

    void PongGame::Ball::Move() noexcept
    {
        pos.x += _speed.x;
        pos.y += _speed.y;

        rect.x = pos.x;
        rect.y = pos.y;

        if(pos.y < gameBox.y || rect.y + rect.height > gameBox.y + boxHeight)
        {
            wallHitSound.Play();
            _speed.y *= -1;
        }

        return;
    }

    void PongGame::Ball::Reset() noexcept
    {
        pos = _orig;
        rect.x = _orig.x;
        rect.y = _orig.y;

        return;
    }

    bool PongGame::Ball::IsOut() const noexcept { return (IsOutLeft() || pos.x > gameBox.x + boxWidth); }
    bool PongGame::Ball::IsOutLeft() const noexcept { return (pos.x < gameBox.x); }

    void PongGame::Ball::Collision(const PongGame::Paddle& paddle) noexcept
    {
        if(rect.CheckCollision(paddle.rect))
        {
            paddleHitSound.Play();
            _speed.x *= -1;
        }

        return;
    }
} // namespace Classics