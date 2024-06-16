#include <games/spaceinvaders.hpp>

namespace Classics
{
    InvadersGame::Bullet::Bullet(float x, float y, Direction dir):
        GameObjectRectangle{x, y, bulletDim.x, bulletDim.y, rl::Color{173, 204, 96, 255}},
        _dir{dir}
    {}

    void InvadersGame::Bullet::Move() noexcept
    {
        switch(_dir)
        {
            case Direction::UP:    pos.y -= bulletSpeed; break;
            case Direction::DOWN:  pos.y += bulletSpeed; break;
        }

        rect.x = pos.x;
        rect.y = pos.y;

        return;
    }

    void InvadersGame::Bullet::Reset()
    {
        SetPos({-1, -1});
        return;
    }

    bool InvadersGame::Bullet::IsOut() const noexcept { return (pos.y < gameBounds.y || pos.y > gameBounds.w); }

    void InvadersGame::Bullet::ChangeFrame() noexcept
    {
        _frame = !_frame;
        return;
    }

    bool InvadersGame::Bullet::CheckCollision(const rl::Rectangle& other) const
    {
        return (rect.CheckCollision(other));
    }
} // namespace Classics