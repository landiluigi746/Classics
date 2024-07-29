#include <games/pong.hpp>

namespace Classics
{
    PongGame::Paddle::Paddle(float x, float y, int keyUp, int keyDown):
        GameObjectRectangle{x, y, paddleWidth, paddleHeight, rl::Color::DarkGray()},
        _keyUp{keyUp},
        _keyDown{keyDown},
        _score{0},
        _orig{x, y}
    {}

    void PongGame::Paddle::Move()
    {
        if(IsKeyDown(_keyUp) && rect.y > gameBox.y + boxThickness)
            rect.y -= paddleSpeed;
        
        if(IsKeyDown(_keyDown) && rect.y + rect.height < gameBox.y + boxHeight)
            rect.y += paddleSpeed;
        
        return;
    }

    void PongGame::Paddle::Reset() noexcept
    {
        pos = _orig;
        rect.x = _orig.x;
        rect.y = _orig.y;

        return;
    }

    void PongGame::Paddle::IncrementScore() noexcept
    {
        ++_score;
        return;
    }

    int PongGame::Paddle::GetScore() const noexcept { return _score; }
} // namespace Classics