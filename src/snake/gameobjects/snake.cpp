#include <games/snake.hpp>

namespace Classics
{
    SnakeGame::Snake::Snake(int x, int y):
        GameObjectRectangle{x, y, cellSize, cellSize},
        _dir{Direction::UP},
        _length{baseLength}
    {
        _body.resize(rowCells * colCells + 1);

        for(int i = 0; i < _length; i++)
            _body[i] = rl::Vector2{pos.x, pos.y + i};
    }

    void SnakeGame::Snake::Move()
    {
        auto& head = _body.front();

        if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && _dir != Direction::DOWN)
            _dir = Direction::UP;
        else if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && _dir != Direction::RIGHT)
            _dir = Direction::LEFT;
        else if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && _dir != Direction::UP)
            _dir = Direction::DOWN;
        else if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && _dir != Direction::LEFT)
            _dir = Direction::RIGHT;

        for(int i = _length; i > 0; i--)
            _body[i] = _body[i - 1];

        switch(_dir)
        {
            case Direction::UP:     head.y--; break;
            case Direction::LEFT:   head.x--; break;
            case Direction::DOWN:   head.y++; break;
            case Direction::RIGHT:  head.x++; break;
        }

        pos = head;
        rect.SetPosition(head);

        return;
    }

    void SnakeGame::Snake::Draw(float roundness, int segments) const
    {
        ::DrawRectangleRounded({offset + _body[0].x * cellSize, offset + _body[0].y * cellSize, cellSize, cellSize}, 0.2f, 1, rl::Color::SkyBlue());

        for(int i = 1; i < _length; i++)
            ::DrawRectangle(offset + _body[i].x * cellSize, offset + _body[i].y * cellSize, cellSize, cellSize, rl::Color::SkyBlue());
    
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