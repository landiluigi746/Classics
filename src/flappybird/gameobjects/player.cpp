#include <games/flappybird.hpp>

namespace Classics
{
    FlappyBirdGame::Player::Player(float x, float y):
        GameObjectTexturized{x, y, TEXTURES_PATH(flappybird) + "player.png"},
        _frame{0},
        _timer{0}
    {}

    void FlappyBirdGame::Player::Move()
    {
        float frameTime = GetFrameTime();

        _timer += frameTime;

        if(IsKeyDown(KEY_SPACE))
        {
            pos.y -= playerJumpForce * frameTime;
            _timer = 0.0f;
            _rotation = jumpRotation;
            if(!wingSound.IsPlaying())
                wingSound.Play();
        }
        
        if(_timer > jumpTick)
        {
            pos.y += gravity * frameTime;
            
            if(_rotation < downRotation)
                _rotation += 6.0f;
        }

        return;
    }

    void FlappyBirdGame::Player::Draw() const
    {
        rl::Rectangle source{_frame * texture.width / 3, 0, (float)texture.width / 3, texture.height};
        rl::Rectangle dest{pos.x, pos.y, source.width * scaleFactor, source.height * scaleFactor};
        rl::Vector2 origin{dest.width / 2, dest.height / 2};

        texture.Draw(source, dest, origin, _rotation);

        //debug stuff
        //::DrawCircleLinesV(pos, dest.width / 2, RAYWHITE);

        //::DrawLine((int)gameBounds.x, (int)pos.y, (int)gameBounds.z, (int)pos.y, RAYWHITE);
        //::DrawLine((int)pos.x, (int)gameBounds.y, (int)pos.x, (int)gameBounds.w, RAYWHITE);

        return;
    }

    void FlappyBirdGame::Player::ChangeFrame()
    {
        (_frame < 2) ? _frame++ : _frame = 0;
        return;
    }

    bool FlappyBirdGame::Player::GroundColliding() const noexcept { return (pos.y + texture.height > gameBounds.w - baseHeight); }
} // namespace Classics