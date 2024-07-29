#include <games/dino.hpp>

namespace Classics
{
    float DinoGame::groundEndY = 0.0f;
    rl::Sound DinoGame::pressSound = rl::Sound{};

    void DinoGame::Animations()
    {
        runner.ChangeFrame();

        for(auto& obstacle: obstacles)
            obstacle.ChangeFrame();

        return;
    }

    void DinoGame::Start()
    {
        curr_time = GetTime();
        spawn_time = GetTime();

        hitSound = rl::Sound{SOUNDS_PATH(dino) + "hit.ogg"};
        pressSound = rl::Sound{SOUNDS_PATH(dino) + "press.ogg"};

        ground = rl::Texture2D{TEXTURES_PATH(dino) + "ground.png"};
        clouds = rl::Texture2D{TEXTURES_PATH(dino) + "clouds.png"};

        groundScroll = 0.0f;
        cloudsScroll = 0.0f;

        groundEndY = center.y + clouds.height + ground.height;

        runner = Runner(gameBounds.x + 32, groundEndY - 65);
        obstacles.clear();

        score = 0;

        return;
    }

    bool DinoGame::Update()
    {
        {
            groundScroll += 5.5f;
            cloudsScroll += 6.0f;

            double time = GetTime();

            runner.Move();

            if(time >= spawn_time + spawnTick)
            {
                spawn_time = time;

                if(::GetRandomValue(1, 20) < 2)
                    obstacles.emplace_back(Bird(gameBounds.z));
                else
                    obstacles.emplace_back(Obstacle(gameBounds.z));
            }

            if(time >= curr_time + frameTick)
            {
                curr_time = time;
                Animations();
            }

            if(!obstacles.front().Exists())
                obstacles.erase(obstacles.begin());
            
            for(auto& obstacle: obstacles)
            {
                obstacle.Move();

                if(obstacle.IsColliding(runner))
                {
                    hitSound.Play();
                    Wait(1000);
                    return false;
                }

                if(!obstacle.passed && obstacle.pos.x + obstacle.texture.width < runner.pos.x)
                {
                    score += 10;
                    obstacle.passed = true;
                }
            }
        }

        p_window.BeginDrawing();

        {
            rl::Rectangle ground_source{ground.width / 2 + groundScroll, 0, ground.width / 2, ground.height};
            rl::Rectangle ground_dest{gameBounds.x, center.y + clouds.height, boxWidth, ground_source.height};

            rl::Rectangle clouds_source{clouds.width / 2 + cloudsScroll, 0, clouds.width / 2, clouds.height};
            rl::Rectangle clouds_dest{gameBounds.x, center.y - ground.height, boxWidth, clouds_source.height};

            p_window.ClearBackground(p_bgColor);
            gameBox.DrawLines(rl::Color::Gray(), boxThickness);

            ground.Draw(ground_source, ground_dest);
            clouds.Draw(clouds_source, clouds_dest);

            runner.Draw();

            for(auto& obstacle: obstacles)
                obstacle.Draw();
            
            char scoreText[20];
            sprintf_s(scoreText, "Score: %d", score, obstacles.size());
            ::DrawText(scoreText, center.x - ::MeasureText(scoreText, 32) / 2, gameBounds.y - offset / 2, 32, BLACK);
        }

        p_window.EndDrawing();

        return (!IsKeyDown(KEY_Q));
    }

    void DinoGame::End()
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
} // namespace Classsics