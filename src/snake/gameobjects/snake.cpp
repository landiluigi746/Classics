#include <games/snake.hpp>

#define _UP    rl::Vector2{0, -1}
#define _LEFT  rl::Vector2{-1, 0}
#define _DOWN  rl::Vector2{0, 1}
#define _RIGHT rl::Vector2{1, 0}

namespace Classics
{
    SnakeGame::Snake::Snake(int x, int y):
        GameObjectRectangle{x, y, cellSize, cellSize},
        _dir{0, -1},
        _length{baseLength}
    {
        _body.resize(rowCells * colCells + 1);

        for(int i = 0; i < _length; i++)
            _body[i] = rl::Vector2{pos.x, pos.y + i};
    }

    void SnakeGame::Snake::Move()
    {
        auto& head = _body.front();

        if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && _dir.y != 1)
            _dir = _UP;
        else if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && _dir.x != 1)
            _dir = _LEFT;
        else if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && _dir.y != -1)
            _dir = _DOWN;
        else if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && _dir.x != -1)
            _dir = _RIGHT;

        for(int i = _length; i > 0; i--)
            _body[i] = _body[i - 1];

        head += _dir;
        pos = head;
        rect.SetPosition(head);

        return;
    }

    void SnakeGame::Snake::Draw(float roundness, int segments) const
    {
        rl::Rectangle rect;

        for(int i = 0; i < _length; i++)
        {
            rect = rl::Rectangle{offset + _body[i].x * cellSize, offset + _body[i].y * cellSize, cellSize, cellSize};
            rect.Draw(rl::Color::SkyBlue());
        }

        return;
    }

    int SnakeGame::Snake::GetScore() const noexcept { return _length - baseLength; }

    void SnakeGame::Snake::AddSegment() noexcept
    {
        ++_length;
        return;
    }

    bool SnakeGame::Snake::SelfCollision() const noexcept
    {
        for(int i = 1; i < _length; i++)
            if(_body[i] == _body.front())
                return true;
        
        return false;
    }

    bool SnakeGame::Snake::WallCollision() const noexcept { return (pos.x < 0 || pos.x > colCells - 1 || pos.y < 0 || pos.y > rowCells - 1); }

    bool SnakeGame::Snake::Contains(rl::Vector2 pos) const noexcept
    {
        for(int i = 0; i < _length; i++)
            if(pos == _body[i])
                return true;
        
        return false;
    }
} // namespace Classics