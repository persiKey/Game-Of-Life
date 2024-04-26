#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H


#include <memory>

#include "IGOF.hpp"
#include "IGOFAlgorithm.hpp"
#include "ICheckBoardFiller.hpp"

namespace GameOfLife
{

class BorderCheckBoardGOF : public IGOF
{
public:
    BorderCheckBoardGOF(index_t length,
               index_t height,
               std::unique_ptr<IBorderGOFAlgorithm> &&solver,
               std::unique_ptr<ICheckBoardFiller> filler);

    const ICheckBoard& GetCheckBoard() const;
    const ICheckBoard& NextStep();
    std::size_t GetCurrentStep() const;

private:
    std::shared_ptr<IBorderCheckBoard> m_checkboard;
    std::shared_ptr<IBorderCheckBoard> m_checkboard_buffer;
    std::unique_ptr<IBorderGOFAlgorithm> m_solver;
};


}

#endif