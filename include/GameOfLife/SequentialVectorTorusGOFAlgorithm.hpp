#ifndef SEQUENTIAL_VECTOR_TORUS_GOF_ALGORITHM
#define SEQUENTIAL_VECTOR_TORUS_GOF_ALGORITHM

#include "IGOFAlgorithm.hpp"
#include "VectorBorderCheckBoard.hpp"
#include <atomic>

namespace GameOfLife
{

class SequentialVectorTorusGOFAlgorithm : public IVectorBorderGOFAlgorithm
{
public:
    virtual void Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state, 
                         std::shared_ptr<VectorBorderCheckBoard>& m_next_state) override;

    static void ComputeVectorChunk(index_t begin,
                                   index_t end,
                                   std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                                   std::shared_ptr<VectorBorderCheckBoard>& m_next_state);

    static void FillCorners(std::shared_ptr<VectorBorderCheckBoard>& m_current_state);

    static void FillRowsChunk(index_t begin,
                              index_t end,
                              std::shared_ptr<VectorBorderCheckBoard>& m_current_state);

    static void FillColumnsChunk(index_t begin,
                                 index_t end,
                                 std::shared_ptr<VectorBorderCheckBoard>& m_current_state);

    static std::atomic_int64_t counter;
};
}
#endif
