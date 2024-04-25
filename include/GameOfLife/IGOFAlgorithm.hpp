#ifndef IGOF_ALGORITHM_HPP
#define IGOF_ALGORITHM_HPP

#include "ICheckBoard.hpp"
#include <memory>

namespace GameOfLife
{

class IBorderGOFAlgorithm
{
public:
    IBorderGOFAlgorithm() = default;
    virtual ~IBorderGOFAlgorithm() = default;

    virtual void Compute(std::shared_ptr<IBorderCheckBoard> m_current_state, 
                         std::shared_ptr<IBorderCheckBoard> m_next_state) = 0;
};

}


#endif