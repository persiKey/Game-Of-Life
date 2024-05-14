#ifndef IGOF_ALGORITHM_HPP
#define IGOF_ALGORITHM_HPP

#include "ICheckBoard.hpp"
#include "VectorBorderCheckBoard.hpp"
#include <memory>

namespace GameOfLife
{

class IGOFAlgorithm
{
protected:
    inline static void CellChecker(uint8_t& neighbors_counter, cell_t cell)
    {
        if (cell == cell_t::ALIVE)
        {
            neighbors_counter <<= 1;
        }
        //neighbors_counter = neighbors_counter << ((static_cast<uint8_t>(cell) & static_cast<uint8_t>(ALIVE_FLAG)) >> 2);
    }
};

class IBorderGOFAlgorithm : public IGOFAlgorithm
{
public:
    IBorderGOFAlgorithm() = default;
    virtual ~IBorderGOFAlgorithm() = default;

    virtual void Compute(std::shared_ptr<IBorderCheckBoard> m_current_state, 
                         std::shared_ptr<IBorderCheckBoard> m_next_state) = 0;

protected:
    void FillBorder(std::shared_ptr<IBorderCheckBoard> m_current_state);
};

class IVectorBorderGOFAlgorithm : public IGOFAlgorithm
{
public:
    virtual void Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                         std::shared_ptr<VectorBorderCheckBoard>& m_next_state) = 0;
};

}


#endif