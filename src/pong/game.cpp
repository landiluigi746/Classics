#include <games/pong.hpp>

namespace Classics
{
    std::vector<rl::Sound> PongGame::sounds = std::vector<rl::Sound>();

    void PongGame::Start()
    {
        ball = Ball(center.x, center.y);
        player1 = Paddle(gameBox.x + boxThickness, center.y - paddleHeight / 2, KEY_W, KEY_S);
        player2 = Paddle(gameBox.x + gameBox.width - paddleWidth - boxThickness, center.y - paddleHeight / 2, KEY_UP, KEY_DOWN);

        sounds.resize(3);

        sounds[0] = rl::Sound{SOUNDS_PATH(pong) + "paddle_hit.ogg"};
        sounds[1] = rl::Sound{SOUNDS_PATH(pong) + "wall_hit.ogg"};
        sounds[2] = rl::Sound{SOUNDS_PATH(pong) + "score.ogg"};

        return;
    }

    bool PongGame::Update()
    {
        {
            ball.Collision(player1);
            ball.Collision(player2);
            
            ball.Move();
            player1.Move();
            player2.Move();

            if(ball.Out())
            {
                if(ball.OutLeft())
                    player2.IncrementScore();
                else
                    player1.IncrementScore();
                
                ball.Reset();
                player1.Reset();
                player2.Reset();

                sounds[2].Play();
                Wait(1000);
            }

            if(player1.GetScore() >= maximumScore)
                winner = 1;
            
            if(player2.GetScore() >= maximumScore)
                winner = 2;
        }

        p_window.BeginDrawing();

        {
            p_window.ClearBackground(p_bgColor);
            gameBox.DrawLines(rl::Color::DarkGray(), boxThickness);
            ::DrawLine(center.x, gameBox.y, center.x, gameBox.y + gameBox.height, rl::Color::DarkGray());

            ball.Draw(1.1f, 4);
            player1.Draw(1.1f, 8);
            player2.Draw(1.1f, 8);

            char score1[10];
            ::sprintf_s(score1, 9, "%d", player1.GetScore());

            char score2[10];
            sprintf_s(score2, 9, "%d", player2.GetScore());

            ::DrawText(score1, windowWidth / 2 - offset - ::MeasureText(score1, 20), offset / 2 - 10, 20, rl::Color::DarkGray());
            ::DrawText(score2, windowWidth / 2 + offset, offset / 2 - 10, 20, rl::Color::DarkGray());
        }

        p_window.EndDrawing();

        return (!IsKeyDown(KEY_Q) && winner != 1 && winner != 2);
    }

    void PongGame::End()
    {
        char str_winner[] = "Player   wins!";
        str_winner[7] = '0' + winner;

        rl::Text text{::GetFontDefault(), str_winner, 30, spacing, rl::Color::DarkGray()};
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