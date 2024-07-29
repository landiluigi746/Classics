#ifndef CLASSICS_COMMONS_PROGRAM_HPP
#define CLASSICS_COMMONS_PROGRAM_HPP

#include <common/utils.hpp>

namespace Classics
{
    class Program
    {
        public:
            Program(rl::Window& window, const std::string& name, rl::Color bgColor = rl::Color{255, 255, 255, 255}):
                p_window{window}, p_bgColor{bgColor}, _name{name}
            {}

            void Run()
            {
                LoadingScreen();
                Start();
                while(Update() && !p_window.ShouldClose());
                End();

                return;
            }

            std::string GetName() { return _name; }
        protected:
            rl::Window p_window;
            rl::Color p_bgColor;

            virtual void Start() = 0;
            virtual bool Update() = 0;
            virtual void End() = 0;

            virtual void LoadingScreen()
            {
                rl::Font font = ::GetFontDefault();
                rl::Text loading_text{"Starting " + _name, 28, rl::Color::RayWhite(), font, spacing };

                auto textWidth = font.MeasureText(loading_text.text, loading_text.fontSize, spacing).x;

                Vector2 starting_pos{windowWidth / 2 - textWidth / 2, windowHeight / 2};

                rl::Rectangle progress_bar{{windowWidth / 2 - 20, starting_pos.y + 28}, {0, 28}};

                while(progress_bar.width < 40 && !p_window.ShouldClose())
                {
                    p_window.BeginDrawing();

                    {
                        p_window.ClearBackground(rl::Color::Black());
                        loading_text.Draw(starting_pos.x, p_window.GetHeight() / 2 - 28);
                        progress_bar.Draw(rl::Color::RayWhite());
                        progress_bar.width += 7.0f;
                    }

                    p_window.EndDrawing();
                }

                return;
            }
        private:
            std::string _name;
    };
} // namespace Classics

#endif // !CLASSICS_COMMONS_PROGRAM_HPP