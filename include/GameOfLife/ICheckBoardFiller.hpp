//
// Created by persiKey on 4/25/24.
//

#ifndef I_CHECKBOARD_FILLER_HPP
#define I_CHECKBOARD_FILLER_HPP

#include "ICheckBoard.hpp"
#include <memory>

namespace GameOfLife
{
class ICheckBoardFiller
{
public:
    ICheckBoardFiller() = default;
    virtual ~ICheckBoardFiller() = default;

    virtual void Fill(std::shared_ptr<ICheckBoard> checkboard) = 0;
};
}

#endif
