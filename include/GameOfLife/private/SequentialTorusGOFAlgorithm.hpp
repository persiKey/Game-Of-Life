#ifndef SEQUENTIAL_TORUS_GOF_ALGORITHM
#define SEQUENTIAL_TORUS_GOF_ALGORITHM

#include "IGOFAlgorithm.hpp"

namespace GameOfLife
{

class SequentialTorusGOFAlgorithm : public IBorderGOFAlgorithm
{
public:
    virtual void Compute(std::shared_ptr<const IBorderCheckBoard> m_current_state, 
                         std::shared_ptr<IBorderCheckBoard> m_next_state) override;
};


}

#endif