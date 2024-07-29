#include <headers.hpp>

int main()
{
    rl::Window window(cl::windowWidth, cl::windowHeight, "Classics");
    rl::AudioDevice audioDevice;
    window.SetTargetFPS(60);

    int OFFSET = 20;
    int TITLE_FONT_SIZE = 30;
    int GAMES_FONT_SIZE = 20;
    float SPACING = 2.0f;

    std::size_t selected = 0;
    std::vector<std::unique_ptr<cl::Program>> games;
    std::vector<rl::Text> menuOptions;
    rl::Font font = ::GetFontDefault();
    rl::Text title{"Classics Launcher", TITLE_FONT_SIZE, rl::Color::RayWhite(), font};

    games.emplace_back(std::make_unique<cl::SnakeGame>(window));
    games.emplace_back(std::make_unique<cl::PongGame>(window));
    games.emplace_back(std::make_unique<cl::InvadersGame>(window));
    games.emplace_back(std::make_unique<cl::FlappyBirdGame>(window));
    games.emplace_back(std::make_unique<cl::DinoGame>(window));

    menuOptions.reserve(games.size() + 1);

    for(const auto& game: games)
        menuOptions.emplace_back(game->GetName());
    menuOptions.emplace_back("Exit");

    while(!window.ShouldClose())
    {
        {
            auto exit = menuOptions.size() - 1;

            if(IsKeyPressed(KEY_ENTER))
            {
                if(selected != exit) {games[selected]->Run();}
                else break;
            }

            if(IsKeyPressed(KEY_UP))
                selected = (selected == 0) ? menuOptions.size() - 1 : selected - 1;
            
            if(IsKeyPressed(KEY_DOWN))
                selected = (selected == menuOptions.size() - 1) ? 0 : selected + 1;
        }

        window.BeginDrawing();

        {
            window.ClearBackground(rl::Color::Black());

            rl::Rectangle bounds{{10, 10}, {window.GetWidth() - 20, window.GetHeight() - 20}};
            bounds.DrawLines(rl::Color::RayWhite(), 1.2f);

            ::DrawLine(10, OFFSET * 2 + TITLE_FONT_SIZE + 10, window.GetWidth() - 10, OFFSET * 2 + TITLE_FONT_SIZE + 10, rl::Color::RayWhite());

            rl::Color rectangleColor = rl::Color::Black();
            rl::Color textColor = rl::Color::RayWhite();

            font.DrawText(title.GetText(), window.GetWidth() / 2 - font.MeasureText(title.GetText(), TITLE_FONT_SIZE, SPACING).x / 2, OFFSET + 10, title.GetFontSize(), SPACING, textColor);

            auto size = menuOptions.size();
            for(size_t i = 0; i < size; i++)
            {
                if(i == selected)
                {
                    rectangleColor = rl::Color::RayWhite();
                    textColor = rl::Color::DarkGray();
                }
                else
                {
                    rectangleColor = rl::Color::Black();
                    textColor = rl::Color::RayWhite();
                }

                int textWidth = font.MeasureText(menuOptions[i].GetText(), GAMES_FONT_SIZE, SPACING).x;
                int optionX = window.GetWidth() / 2 - textWidth / 2;
                int optionY = window.GetHeight() / 2 - (OFFSET * 2 + TITLE_FONT_SIZE) + i * (GAMES_FONT_SIZE + OFFSET / 2);

                rectangleColor.DrawRectangle(optionX, optionY, textWidth, GAMES_FONT_SIZE);
                font.DrawText(menuOptions[i].GetText(), optionX, optionY, GAMES_FONT_SIZE, SPACING, textColor);
            }
        }

        window.EndDrawing();
    }

    return 0;
}