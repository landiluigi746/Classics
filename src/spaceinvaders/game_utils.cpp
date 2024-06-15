#include <games/spaceinvaders.hpp>
#include <algorithm>

#define BULLET_TEXTURE TEXTURES_PATH(spaceinvaders) + "enemy_bullet.png"

namespace Classics
{
    void InvadersGame::InitLevel()
    {
        invadersSpeed = defaultInvadersSpeed;

        invaders.clear();
        invadersBullets.clear();
        barriers.clear();
        barriers.resize(4);

        playerBullet = Bullet(-1, -1, Direction::UP);

        for(int i = 0; i < 5; i++)
        {
            std::string texture = TEXTURES_PATH(spaceinvaders);

            switch(i)
            {
                case 0: case 1: texture += "invader1.png"; break;
                case 2: case 3: texture += "invader2.png"; break;
                case 4:         texture += "invader3.png"; break;
            }

            for(int j = 0; j < rowInvaders; j++)
                invaders.emplace_back(gameBounds.x + offset + textureSize * 2 * j, center.y - offset - i * 32, scores[i / 2], texture);
        }

        for(int i = 0; i < 4; i++)
            barriers[i] = Barrier(gameBounds.x + offset * 2 + barrierWidth * 5 * i, player.pos.y - textureSize * 2);

        return;
    }

    void InvadersGame::InvadersBehavior()
    {
        int rng;
        rl::Vector2 first_pos = invaders.front().pos;
        rl::Vector2 last_pos = invaders.front().pos;

        for(const auto& invader: invaders)
        {
            if(invader.pos.x < first_pos.x)
                first_pos = invader.pos;
            
            if(invader.pos.x > last_pos.x)
                last_pos = invader.pos;
        }

        if(first_pos.x <= gameBounds.x || last_pos.x + textureSize >= gameBounds.z)
            for(auto& invader: invaders)
                invader.GoForward();
        
        for(auto invader = invaders.begin(); invader != invaders.end();)
        {
            invader->Move();
            if(!playerBullet.Collision(invader->GetRect()))
            {
                invader->Move();
                ++invader;
            }
            else
            {
                player.GainScore(invader->GetScore());
                sounds[3].Play();
                playerBullet.Reset();
                invader = invaders.erase(invader);
                invadersSpeed += 1 / invaders.size();
            }
        }

        if(specialInvader.pos.x > windowWidth)
            specialInvader.pos.x = -1;

        if((float)(rand() % 100) < level * 9.5f && specialInvader.pos.x < 0)
            specialInvader = Invader(-1, gameBounds.y + offset, scores[3], TEXTURES_PATH(spaceinvaders) + "invader4.png");

        return;
    }

    void InvadersGame::BulletsBehavior()
    {
        for(auto bullet = invadersBullets.begin(); bullet != invadersBullets.end();)
        {
            bool playerHit = bullet->Collision(player.GetRect());
            bool playerBulletCollision = bullet->Collision(playerBullet.rect);

            if(!bullet->Out() && !playerHit && !playerBulletCollision)
            {
                bullet->Move();
                ++bullet;
            }
            else
            {
                bullet->Reset();
                bullet = invadersBullets.erase(bullet);

                if(playerBulletCollision)
                    playerBullet.Reset();
                
                if(playerHit)
                {
                    sounds[2].Play();
                    Wait(1000);
                    playerBullet.Reset();
                    invadersBullets.clear();
                    player.DecrementLives();
                }
            }
        }

        return;
    }

    void InvadersGame::InvadersShoot()
    {
        int rng;

        for(auto& invader: invaders)
        {
            rng = rand() % 100;

            if(rng < 2 + level + (1 / invaders.size()))
            {
                invadersBullets.emplace_back(invader.pos.x + textureSize / 2, invader.pos.y + textureSize, Direction::DOWN);
                sounds[0].Play();
            }
        }

        return;
    }

    void InvadersGame::BarriersBehavior()
    {
        for(auto barrier = barriers.begin(); barrier != barriers.end();)
        {
            auto& blocks = barrier->GetBlocks();

            for(auto block = blocks.begin(); block != blocks.end();)
            {
                if(playerBullet.Collision(rl::Rectangle{block->x, block->y, blockDim.x, blockDim.y}))
                {
                    block = blocks.erase(block);
                    playerBullet.Reset();
                }
                else
                    ++block;
            }

            for(auto bullet = invadersBullets.begin(); bullet != invadersBullets.end();)
            {
                bool toErase = false;

                for(auto block = blocks.begin(); block != blocks.end();)
                {
                    if(bullet->Collision(rl::Rectangle{block->x, block->y, bulletDim.x, bulletDim.y}))
                    {
                        block = blocks.erase(block);
                        bullet->Reset();
                        toErase = true;
                    }
                    else
                        ++block;
                }

                if(toErase)
                    bullet = invadersBullets.erase(bullet);
                else
                    ++bullet;
            }

            if(!barrier->Exists())
                barrier = barriers.erase(barrier);
            else
                barrier++;
        }

        return;
    }

    bool InvadersGame::InvadersWin()
    {
        for(auto& invader: invaders)
            if(invader.pos.y > player.pos.y - textureSize * 2)
                return true;
        
        return false;
    }

    void InvadersGame::Animations()
    {
        for(auto& invader: invaders)
            invader.ChangeFrame();
        
        for(auto& bullet: invadersBullets)
            bullet.ChangeFrame();

        return;
    }

    void InvadersGame::Sounds()
    {
        if(specialInvader.pos.x > 0)
            sounds[1].Play();
    }
} // namespace Classics