#include <games/spaceinvaders.hpp>

namespace Classics
{
    InvadersGame::Barrier::Barrier(float x, float y):
        GameObject{x, y}
    {
        for(int i = 0; i < barrierHeight; i++)
            for(int j = 0; j < barrierWidth; j++)
                _blocks.emplace_back((baseBarrier[i][j]) ? rl::Vector2{x + j * blockDim.x, y + i * blockDim.y} : rl::Vector2{-1, -1});
    }

    void InvadersGame::Barrier::Draw() const
    {
        for(const auto& block: _blocks)
            ::DrawRectangleV(block, blockDim, (Color){173, 204, 96, 255});

        return;
    }

    bool InvadersGame::Barrier::Exists() const noexcept { return (_blocks.size() > 0); }

    std::list<rl::Vector2>& InvadersGame::Barrier::GetBlocks() noexcept { return _blocks; }
} // namespace Classics