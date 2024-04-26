#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <cstddef>
#include <memory>

#include "ICheckBoard.hpp"
#include "IGOFAlgorithm.hpp"
#include "RandomFiller.hpp"

namespace GameOfLife
{

class GOF
{
public:
    GOF(index_t length,
               index_t height,
               std::unique_ptr<IBorderGOFAlgorithm> &&solver,
               std::unique_ptr<ICheckBoardFiller> filler);

    const ICheckBoard& GetCheckBoard() const;
    const ICheckBoard& NextStep();
    std::size_t GetCurrentStep() const;

private:
    std::shared_ptr<IBorderCheckBoard> m_checkboard;
    std::shared_ptr<IBorderCheckBoard> m_checkboard_buffer;
    std::size_t m_step;
    std::unique_ptr<IBorderGOFAlgorithm> m_solver;

};

}

#endif