#ifndef I_CHECK_BOARD_HPP
#define I_CHECK_BOARD_HPP

#include "GOFTypes.hpp"

namespace GameOfLife
{

class ICheckBoard
{
public:
    ICheckBoard() = default;
    virtual ~ICheckBoard() = default;

    virtual cell_t get(index_t i, index_t j) = 0;
    virtual void set(index_t i, index_t j, cell_t value) = 0;

protected:
    index_t m_checkboard_length;
    index_t m_checkboard_heigh;
};

}

#endif