//
// Created by persikey on 4/25/24.
//

#ifndef RANDOM_FILLER_HPP
#define RANDOM_FILLER_HPP

#include "ICheckBoardFiller.hpp"

namespace GameOfLife
{

class RandomFiller : public ICheckBoardFiller
{
public:
    RandomFiller(double alpha);
    void Fill(std::shared_ptr<ICheckBoard> checkboard) override;
private:
    double m_alpha;
};

} // GameOfLife

#endif
