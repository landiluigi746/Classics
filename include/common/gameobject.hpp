#ifndef CLASSICS_COMMONS_GAMEOBJECT_HPP
#define CLASSICS_COMMONS_GAMEOBJECT_HPP

#include <common/utils.hpp>

namespace Classics
{
    class GameObject
    {
        public:
            GameObject(float x, float y):
                pos{x, y}
            {}

            GETTERSETTER(float, X, pos.x)
            GETTERSETTER(float, Y, pos.y)
            GETTERSETTER(rl::Vector2, Pos, pos)

            rl::Vector2 pos;
    };

    class GameObjectTexturized : public GameObject
    {
        public:
            GameObjectTexturized(float x, float y, rl::Texture2D&& texture):
                GameObject{x, y},
                texture{std::move(texture)}
            {}

            virtual void Draw() const
            {
                texture.Draw(pos);
                return;
            }

            virtual rl::Rectangle GetRect() const { return rl::Rectangle{pos.x, pos.y, (float)texture.width, (float)texture.height}; }

            rl::Texture2D texture;
    };

    class GameObjectRectangle : public GameObject
    {
        public:
            GameObjectRectangle(float x, float y, float width, float height, rl::Color color = {255, 255, 255, 255}):
                GameObject{x, y},
                rect{x, y, width, height},
                color{color}
            {}

            virtual void Draw(float roundness = 0.0f, int segments = 0) const
            {
                if(roundness <= 0.0f)
                    rect.Draw(color);
                else
                    rect.DrawRounded(roundness, segments, color);
                
                return;
            }

            rl::Rectangle rect;
            rl::Color color;
    };

    template<typename Container>
    inline void DrawObjects(const Container& gameObjects)
    {
        for(const auto& gameObject: gameObjects)
            gameObject.Draw();
        
        return;
    }
} // namespace Classics

#endif // !CLASSICS_COMMONS_GAMEOBJECT_HPP