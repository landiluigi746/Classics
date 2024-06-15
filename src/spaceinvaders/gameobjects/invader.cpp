#include <games/spaceinvaders.hpp>

namespace Classics
{
    InvadersGame::Invader::Invader(float x, float y, int score, rl::Texture2D&& texture):
        GameObjectTexturized{x, y, std::move(texture)},
        _score{score},
        _frame{0},
        _dir{Direction::RIGHT}
    {
        texture.SetWidth(textureSize);
        texture.SetHeight(textureSize);
    }

    void InvadersGame::Invader::Move(float speed) noexcept
    {
        switch(_dir)
        {
            case Direction::LEFT:   pos.x -= speed; break;
            case Direction::RIGHT:  pos.x += speed; break;
        }

        return;
    }

    void InvadersGame::Invader::Draw() const
    {
        rl::Rectangle source{_frame * 16, 0, 16, 16};
        rl::Rectangle dest{pos.x, pos.y, textureSize, textureSize};

        texture.Draw(source, dest, rl::Vector2{0, 0});

        return;
    }

    void InvadersGame::Invader::ChangeFrame() noexcept
    {
        _frame = !_frame;
        return;
    }

    void InvadersGame::Invader::GoForward() noexcept
    {
        pos.y += textureSize / 2;
        _dir = (_dir == Direction::LEFT) ? Direction::RIGHT : Direction::LEFT;
        
        return;
    }

    int InvadersGame::Invader::GetScore() const noexcept { return _score; }

    rl::Rectangle InvadersGame::Invader::GetRect() const { return rl::Rectangle{pos.x, pos.y, textureSize, textureSize}; }
} // namespace Classics