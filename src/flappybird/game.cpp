#include <games/flappybird.hpp>

namespace Classics
{
    double FlappyBirdGame::tick = 0.95f;
    double FlappyBirdGame::curr_time = 0.0f;
    rl::Sound FlappyBirdGame::wingSound = rl::Sound{};

    void FlappyBirdGame::Start()
    {
        obstacles.clear();

        base = rl::Texture2D{TEXTURES_PATH(flappybird) + "base.png"};
        background = rl::Texture2D{TEXTURES_PATH(flappybird) + "background.png"};

        curr_time = GetTime();
        curr_frame_time = GetTime();

        pointSound = rl::Sound{SOUNDS_PATH(flappybird) + "point.ogg"};
        hitSound = rl::Sound{SOUNDS_PATH(flappybird) + "hit.ogg"};
        dieSound = rl::Sound{SOUNDS_PATH(flappybird) + "die.ogg"};
        wingSound = rl::Sound{SOUNDS_PATH(flappybird) + "wing.ogg"};

        score = 0;

        player = Player(center.x, center.y);
        camera = rl::Camera2D{player.pos, rl::Vector2{center.x, center.y}};

        return;
    }

    bool FlappyBirdGame::Update()
    {
        {
            double time = GetTime();

            baseScroll += 2.5f;
            bgScroll += 1.0f;

            if(baseScroll >= base.width) baseScroll = 0.0f;
            if(bgScroll >= background.width) bgScroll = 0.0f;

            if(time >= curr_time + tick)
            {
                curr_time = time;
                obstacles.emplace_back(gameBounds.x + boxWidth, gameBounds.y);
            }

            if(time >= curr_frame_time + frameTick)
            {
                curr_frame_time = time;
                player.ChangeFrame();
            }

            player.Move();

            if(!obstacles.front().Exists())
                obstacles.erase(obstacles.begin());
            
            for(auto& obstacle: obstacles)
            {
                obstacle.Move();

                if(obstacle.IsColliding(player))
                {
                    hitSound.Play();
                    Wait(1000);
                    return false;
                }

                if(!obstacle.passed && obstacle.pos.x + obstacle.texture.width < player.pos.x)
                {
                    ++score;
                    obstacle.passed = true;
                    pointSound.Play();
                }
            }
        }

        p_window.BeginDrawing();
        camera.BeginMode();

        {
            rl::Rectangle bg_source{bgScroll, 0, boxWidth, boxHeight};
            rl::Rectangle bg_dest{gameBounds.x, gameBounds.y, boxWidth, boxHeight};
            
            rl::Rectangle base_source{baseScroll, 0, boxWidth, base.height};
            rl::Rectangle base_dest{gameBounds.x, gameBounds.w - base.height, boxWidth, base.height};

            p_window.ClearBackground(p_bgColor);

            background.Draw(bg_source, bg_dest);
            base.Draw(base_source, base_dest);

            gameBox.DrawLines(rl::Color::Black(), boxThickness);

            for(auto& obstacle: obstacles)
                obstacle.Draw();
            
            player.Draw();
            
            char scoreText[20];
            sprintf_s(scoreText, "Score: %d", score);
            ::DrawText(scoreText, center.x - ::MeasureText(scoreText, 32) / 2, gameBounds.y - offset / 2, 32, BLACK);
        }

        camera.EndMode();
        p_window.EndDrawing();

        return (!IsKeyDown(KEY_Q) && !player.GroundColliding());
    }

    void FlappyBirdGame::End()
    {
        rl::Text text{::GetFontDefault(), "You lost", 30, spacing, rl::Color::Black()};
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