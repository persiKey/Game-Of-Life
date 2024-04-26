#ifndef SEQUENTIAL_VECTOR_TORUS_GOF_ALGORITHM
#define SEQUENTIAL_VECTOR_TORUS_GOF_ALGORITHM

#include "IGOFAlgorithm.hpp"
#include "VectorBorderCheckBoard.hpp"
#include "SequentialTorusGOFAlgorithm.hpp"
namespace GameOfLife
{

class SequentialVectorTorusGOFAlgorithm : public SequentialTorusGOFAlgorithm
{
public:
    void Compute(std::shared_ptr<VectorBorderCheckBoard> m_current_state, 
                         std::shared_ptr<VectorBorderCheckBoard> m_next_state);

};
}
#endif
