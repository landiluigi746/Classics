#include <games/spaceinvaders.hpp>

namespace Classics
{
    double InvadersGame::tick = InvadersGame::defaultTick;
    float InvadersGame::invadersSpeed = InvadersGame::defaultInvadersSpeed;
    
    std::vector<std::vector<bool>> InvadersGame::baseBarrier = {
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    int InvadersGame::barrierWidth = baseBarrier[0].size();
    int InvadersGame::barrierHeight = baseBarrier.size();

    void InvadersGame::Start()
    {
        curr_time = GetTime();

        background = rl::Texture2D{TEXTURES_PATH(spaceinvaders) + "bg.png"};
        backgroundBuildings = rl::Texture2D{TEXTURES_PATH(spaceinvaders) + "bg_buildings.png"};

        background.SetWidth(8);
        background.SetHeight(8);

        backgroundBuildings.SetWidth(32);
        backgroundBuildings.SetWidth(32);

        backgroundMusic = rl::Music{SOUNDS_PATH(spaceinvaders) + "music.mp3"};
        backgroundMusic.Play();

        shootSound = rl::Sound{SOUNDS_PATH(spaceinvaders) + "shoot.ogg"};
        specialInvaderSound = rl::Sound{SOUNDS_PATH(spaceinvaders) + "special_invader.ogg"};
        playerDeathSound = rl::Sound{SOUNDS_PATH(spaceinvaders) + "player_death.ogg"};
        invaderKilledSound = rl::Sound{SOUNDS_PATH(spaceinvaders) + "invader_killed.ogg"};

        player = Player(center.x, boxHeight);

        InitLevel();

        return;
    }

    bool InvadersGame::Update()
    {
        {
            backgroundMusic.Update();

            player.Move();
            playerBullet.Move();
            BulletsBehavior();
            InvadersBehavior();
            BarriersBehavior();

            if(invaders.size() <= 0)
                InitLevel();

            if(IsKeyDown(KEY_SPACE) && playerBullet.IsOut())
            {
                playerBullet.SetPos({player.pos.x + textureSize / 2, player.pos.y - textureSize});
                shootSound.Play();
            }

            if(GetTime() >= curr_time + tick)
            {
                curr_time = GetTime();

                if((float)(rand() % 100) < level * 0.1f && specialInvader.pos.x < 0)
                    specialInvader = Invader(0, gameBounds.y + offset, scores[3], TEXTURES_PATH(spaceinvaders) + "invader4.png");

                InvadersShoot();
                Animations();
                Sounds();
            }
        }

        p_window.BeginDrawing();

        {
            rl::Rectangle bg_source{0, 0, 64, 64};
            rl::Rectangle bg_dest{gameBounds.x, gameBounds.y, boxWidth, boxHeight};
            rl::Vector2 bg_origin{0, 0};

            rl::Rectangle ui_player_source{0, 0, textureSize, textureSize};
            rl::Rectangle ui_player_dest{0, gameBounds.y - offset / 2, 24, 24};

            p_window.ClearBackground(p_bgColor);
            gameBox.DrawLines(rl::Color::Green(), boxThickness);

            background.Draw(bg_source, bg_dest, bg_origin);
            backgroundBuildings.Draw(bg_source, bg_dest, bg_origin);

            char score[40];
            sprintf_s(score, "Score<%d>: %d", level, player.GetScore());
            ::DrawText(score, gameBounds.x, gameBounds.y - offset / 2, 32, RAYWHITE);

            for(int i = player.GetLives(); i > 0; i--)
            {
                ui_player_dest.x = gameBounds.z - (i * textureSize + 2);
                player.texture.Draw(ui_player_source, ui_player_dest);
            }

            player.Draw();
            playerBullet.Draw();
            DrawObjects(invaders);
            DrawObjects(invadersBullets);
            DrawObjects(barriers);

            if(specialInvader.pos.x + textureSize > gameBounds.x && specialInvader.pos.x + textureSize < gameBounds.z)
                specialInvader.Draw();
        }

        p_window.EndDrawing();

        return (!IsKeyDown(KEY_Q) && !InvadersWin() && player.GetLives() > 0);
    }

    void InvadersGame::End()
    {
        backgroundMusic.Stop();

        shootSound.Stop();
        specialInvaderSound.Stop();
        playerDeathSound.Stop();
        invaderKilledSound.Stop();

        rl::Text text{::GetFontDefault(), "You lost", 30, spacing, rl::Color::RayWhite()};
        rl::Vector2 textDim{text.MeasureEx()};

        while(!IsKeyDown(KEY_Q))
        {

            p_window.BeginDrawing();

            p_window.ClearBackground(p_bgColor);
            text.Draw(center.x - textDim.x / 2, center.y - textDim.y / 2);

            p_window.EndDrawing();
        }

        return;
    }
} // namespace Classics