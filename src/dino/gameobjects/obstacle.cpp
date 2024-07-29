#include <games/dino.hpp>

namespace Classics
{
    DinoGame::Obstacle::Obstacle(float x, bool init):
        GameObjectTexturized{x, -1, TEXTURES_PATH(dino) + "cactus1.png"},
        passed{false}
    {
        if(init)
        {
            int r = ::GetRandomValue(1, 3);

            std::string textureStr = TEXTURES_PATH(dino);

            switch(r)
            {
                case 1: textureStr += "cactus1.png"; break;
                case 2: textureStr += "cactus2.png"; break;
                case 3: textureStr += "cactus3.png"; break;
            }

            texture = rl::Texture2D{textureStr};
            pos.y = groundEndY - texture.height;
        }
    }

    void DinoGame::Obstacle::Move()
    {
        pos.x -= obstacleSpeed;

        return;
    }

    void DinoGame::Obstacle::Draw() const
    {
        float x;
        float width;

        if(pos.x > gameBounds.x)
        {
            x = pos.x;
            width = texture.width;

            if(pos.x + texture.width > gameBounds.z)
                width = gameBounds.z - pos.x;
        }
        else
        {
            x = gameBounds.x;
            width = pos.x + texture.width - gameBounds.x;
        }

        rl::Rectangle source{0, 0, texture.width, texture.height};
        rl::Rectangle dest{x, pos.y, width, texture.height};

        texture.Draw(source, dest);

        return;
    }

    bool DinoGame::Obstacle::Exists() const noexcept { return (pos.x + texture.width > gameBounds.x); }

    bool DinoGame::Obstacle::IsColliding(const DinoGame::Runner& runner) const noexcept
    {
        return (GetRect().CheckCollision(runner.GetRect()));
    }
} // namespace Classics