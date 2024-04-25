#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <cstddef>
#include <memory>

#include "ICheckBoard.hpp"
#include "IGOFAlgorithm.hpp"

namespace GameOfLife
{
     
class GameOfLife
{
public:
    GameOfLife(index_t length, index_t heigh, std::unique_ptr<IBorderGOFAlgorithm> solver);

    const ICheckBoard& GetCheckBoard();
    const ICheckBoard& NextStep();
    std::size_t GetCurrentStep();

private:
    std::shared_ptr<IBorderCheckBoard> m_checkboard;
    std::shared_ptr<IBorderCheckBoard> m_checkboard_buffer;
    std::size_t m_step;
    std::unique_ptr<IBorderGOFAlgorithm> m_solver;

};

}

#endif