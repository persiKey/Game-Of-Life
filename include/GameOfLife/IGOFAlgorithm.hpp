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

protected:
    // This function should be in the common interface IGOFAlgorithm, but now there is no need in it
    inline static void CellChecker(uint8_t& neighbors_counter, cell_t cell)
    {
        if (cell == cell_t::ALIVE)
        {
            neighbors_counter <<= 1;
        }
        //neighbors_counter = neighbors_counter << ((static_cast<uint8_t>(cell) & static_cast<uint8_t>(ALIVE_FLAG)) >> 2);
    }
    void FillBorder(std::shared_ptr<IBorderCheckBoard> m_current_state);
};

}


#endif