#include <games/dino.hpp>

namespace Classics
{
    DinoGame::Runner::Runner(float x, float y):
        GameObjectTexturized{x, y, TEXTURES_PATH(dino) + "dino-up.png"},
        upTexture{TEXTURES_PATH(dino) + "dino-up.png"},
        downTexture{TEXTURES_PATH(dino) + "dino-down.png"},
        _frame{0},
        _down{false},
        _jumping{false},
        _acceleration{0.0f},
        _velocity{0.0f}
    {
        texture.SetHeight(64);

        upTexture.SetWidth(64 * 2);
        upTexture.SetHeight(64);

        downTexture.SetWidth(81 * 2);
        downTexture.SetHeight(38);
    }

    void DinoGame::Runner::Move()
    {
        float frameTime = GetFrameTime();

        _down = IsKeyDown(KEY_DOWN);

        if(IsKeyPressed(KEY_SPACE) && !_jumping)
        {
            _acceleration = 0.0f;
            _velocity = -gravity * 2.1f;
            pressSound.Play();
        }
        else if(pos.y + texture.height < groundEndY)
        {
            _jumping = true;
            _acceleration += gravity * frameTime * 8.0f;
        }
        else
        {
            _jumping = false;
            _velocity = 0.0f;
            _acceleration = 0.0f;
        }

        _velocity += _acceleration * frameTime;
        pos.y += _velocity * frameTime;

        if(pos.y + texture.height >= groundEndY)
            pos.y = groundEndY - texture.height;

        return;
    }

    void DinoGame::Runner::Draw() const
    {
        auto& textureToDraw = (_down) ? downTexture : upTexture;
        float y = (_down) ? pos.y + (upTexture.height - downTexture.height) : pos.y;

        rl::Rectangle source{textureToDraw.width / 2 * _frame, 0, textureToDraw.width / 2, textureToDraw.height};
        rl::Rectangle dest{pos.x, y, textureToDraw.width / 2, textureToDraw.height};

        textureToDraw.Draw(source, dest);

        dest.DrawLines(rl::Color::Gray());

        return;
    }

    void DinoGame::Runner::ChangeFrame() noexcept
    {
        _frame = !_frame;
        return;
    }

    rl::Rectangle DinoGame::Runner::GetRect() const
    {
        auto& textureToDraw = (_down) ? downTexture : upTexture;
        float y = (_down) ? pos.y + textureToDraw.height : pos.y;
        return rl::Rectangle{pos.x, y, textureToDraw.width / 2, textureToDraw.height};
    }
} // namespace Classics