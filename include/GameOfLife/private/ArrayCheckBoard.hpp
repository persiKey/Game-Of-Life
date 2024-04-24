#ifndef ARRAY_CHECK_BOARD_HPP
#define ARRAY_CHECK_BOARD_HPP

#include "ICheckBoard.hpp"

namespace GameOfLife
{

class ArrayCheckBoard : public ICheckBoard
{
public:
    ArrayCheckBoard() = default;
    virtual ~ArrayCheckBoard() = default;

    virtual cell_t get(index_t i, index_t j);
    virtual void set(index_t i, index_t j, cell_t value);

private:
    cell_t* m_data;
    const index_t INDEXING_OFFSET;
    index_t m_big_checkboard_lenght;
    index_t m_big_checkboard_height;
};

}

#endif