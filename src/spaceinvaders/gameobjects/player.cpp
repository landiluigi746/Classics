#include <games/spaceinvaders.hpp>

namespace Classics
{
    InvadersGame::Player::Player(float x, float y):
        GameObjectTexturized{x, y, TEXTURES_PATH(spaceinvaders) + "player.png"},
        _score{0},
        _lives{defaultLives},
        _orig{pos}
    {
        texture.SetWidth(textureSize);
        texture.SetHeight(textureSize);
    }

    void InvadersGame::Player::Move()
    {
        if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && pos.x > gameBox.x + boxThickness)
            pos.x -= playerSpeed;
        
        if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && pos.x < gameBox.width - boxThickness * 2)
            pos.x += playerSpeed;
        
        return;
    }

    void InvadersGame::Player::GainScore(int score) noexcept
    {
        _score += score;
        return;
    }

    int InvadersGame::Player::GetScore() const noexcept { return _score; }

    int InvadersGame::Player::GetLives() const noexcept { return _lives; }

    void InvadersGame::Player::DecrementLives() noexcept
    {
        --_lives;
        return;
    }
} // namespace Classics