#include <games/flappybird.hpp>
#include <algorithm>

namespace Classics
{
    FlappyBirdGame::Obstacle::Obstacle(float x, float y):
        GameObjectTexturized{x, y, TEXTURES_PATH(flappybird) + "pipe.png"},
        passed{false},
        _upperPipeHeight{GetRandomValue(minPipeHeight, pipeHeight)},
        _lowerPipeHeight{pipeHeight + minPipeHeight - _upperPipeHeight}
    {}

    void FlappyBirdGame::Obstacle::Move()
    {
        pos.x -= pipeSpeed;

        return;
    }

    void FlappyBirdGame::Obstacle::Draw() const
    {
        float drawWidth;
        float drawXUpper;
        float drawXLower;
        
        drawXUpper = pos.x;

        if(pos.x > gameBounds.x)
        {
            drawWidth = texture.width;
            drawXLower = pos.x;

            if(pos.x + texture.width > gameBounds.z)
            {
                drawWidth = gameBounds.z - pos.x;
                drawXUpper = gameBounds.z - texture.width;
            }
        }
        else
        {
            drawWidth = pos.x + texture.width - gameBounds.x;
            drawXLower = gameBounds.x;
        }

        rl::Rectangle upper_source{0, 0, texture.width, _upperPipeHeight};
        rl::Rectangle upper_dest{drawXUpper, pos.y, drawWidth, _upperPipeHeight};

        rl::Rectangle lower_source{0, 0, texture.width, _lowerPipeHeight};
        rl::Rectangle lower_dest{drawXLower, gameBounds.w - baseHeight - _lowerPipeHeight, drawWidth, _lowerPipeHeight};

        texture.Draw(lower_source, lower_dest, rl::Vector2{0, 0});
        texture.Draw(upper_source, upper_dest, rl::Vector2{texture.width, _upperPipeHeight}, 180.0f);

        //debug stuff
        //::DrawRectangleLines(pos.x, pos.y, texture.width, _upperPipeHeight, RAYWHITE);
        //::DrawRectangleLines(pos.x, gameBounds.w - baseHeight - _lowerPipeHeight, texture.width, _lowerPipeHeight, RAYWHITE);
    }

    bool FlappyBirdGame::Obstacle::Exists() const noexcept { return pos.x + texture.width > gameBounds.x; }

    bool FlappyBirdGame::Obstacle::IsColliding(const FlappyBirdGame::Player& player) const noexcept
    {
        rl::Rectangle upperRectangle{pos.x, pos.y, texture.width, _upperPipeHeight};
        rl::Rectangle lowerRectangle{pos.x, gameBounds.w - baseHeight - _lowerPipeHeight, texture.width, _lowerPipeHeight};
        
        float radius = ((float) texture.width / 3 * scaleFactor) / 2;

        return ::CheckCollisionCircleRec(player.pos, radius, upperRectangle) || ::CheckCollisionCircleRec(player.pos, radius, lowerRectangle);
    }
} // namespace Classics
