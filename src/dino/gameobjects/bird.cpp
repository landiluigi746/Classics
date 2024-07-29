#include <games/dino.hpp>

namespace Classics
{
    DinoGame::Bird::Bird(float x):
        Obstacle{x, false},
        _frame{0}
    {
        texture = rl::Texture2D{TEXTURES_PATH(dino) + "bird.png"};
        pos.y = center.y - 4;
        texture.SetWidth(114);
        texture.SetHeight(48);
    }

    void DinoGame::Bird::Draw() const
    {
        float x;
        float width;

        if(pos.x > gameBounds.x)
        {
            x = pos.x;
            width = texture.width / 2;

            if(pos.x + texture.width / 2 > gameBounds.z)
                width = gameBounds.z - pos.x;
        }
        else
        {
            x = gameBounds.x;
            width = pos.x + texture.width / 2 - gameBounds.x;
        }

        rl::Rectangle source{texture.width / 2 * _frame, 0, texture.width / 2, texture.height};
        rl::Rectangle dest{x, pos.y, width, texture.height};

        texture.Draw(source, dest);

        return;
    }

    void DinoGame::Bird::ChangeFrame() noexcept
    {
        _frame = !_frame;
        return;
    }
} // namespace Classics